/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/06 22:21:29 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

void	clear_parse_tree(t_parse *root)
{
	t_parse *left_tree;
	t_parse *right_tree;

	left_tree = root->left;
	right_tree = root->right;
	if (left_tree)
	{
		clear_parse_tree(left_tree);
		free(left_tree);
	}
	if (right_tree)
	{
		clear_parse_tree(right_tree);
		free(right_tree);
	}
	ft_lstclear(&root->node, free);
}


void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	if (parse_tree->is_subshell)
		printf("this is SUBSHELL_NODE\n");
	else
		ft_lstiter(parse_tree->node, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

static int	find_operator(\
	t_lex *lexlst, t_lex **end_of_left_child, t_lex **root_node, e_lexeme type)
{
	t_lexeme	*lex_data;	
	t_lex		*prev_lex;
	int			dquote_flag;
	int			depth_parenthesis;

	dquote_flag = 0;
	depth_parenthesis = 0;
	lex_data = lexlst->content;
	if (lex_data->type == type)
	{
		*root_node = lexlst;
		end_of_left_child = NULL;
		return (1);
	}
	else if (lex_data->type == LEXEME_DQUOTE)
		dquote_flag ^= 1;
	else if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		depth_parenthesis++;
	else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		depth_parenthesis--;
	prev_lex = lexlst;
	lexlst = lexlst->next;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
			depth_parenthesis++;
		else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			depth_parenthesis--;
		else if (depth_parenthesis == 0 && dquote_flag == 0 
			&& lex_data->type == type)
		{
			*root_node = lexlst;
			*end_of_left_child = prev_lex;
			return (1);
		}
		prev_lex = lexlst;
		lexlst = lexlst->next;
	}
	return (0);
}

static int	find_root_node(\
	t_lex *lexlst, t_lex **end_of_left_child, t_lex **root_node)
{
	if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_AND))
		return (1);
	else if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_OR))
		return (1);
	else if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_PIPE))
		return (1);
	else
		return (0);
}

static void	*_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

static t_parse	*operator_parse(t_lex *lexlst) // null 반환시 syntax error
{
	t_parse	*root;
	t_lex	*end_of_left_child;
	t_lex	*root_node;

	root = ft_calloc(1, sizeof(t_parse));
	if (find_root_node(lexlst, &end_of_left_child, &root_node)) // 루트노드를 찾음
	{
		if (end_of_left_child == NULL || root_node->next == NULL) // 오퍼레이터 위치 오류
			return (_free(root));
		end_of_left_child->next = NULL;
		root->left = parse(lexlst);
		if (root->left == NULL)
			return (_free(root));
		root->right = parse(root_node->next);
		if (root->right == NULL)
			return (_free(root));
		root_node->next = NULL;
		root->node = root_node;
		return (root);
	}
	root->node = lexlst;
	return (root);
}

static int	is_root_subshell(t_lex *lexlst)
{
	t_lexeme	*lex_data;

	lex_data = lexlst->content;
	return (lex_data->type == LEXEME_PARENTHESIS_OPEN);
}

static t_lex	*get_prev_last_parenthesis_close(t_lex *lexlst)
{
	int			depth_parenthesis;
	t_lex		*front;
	t_lex		*rear;
	t_lexeme	*lex_data;
	t_lex		*last_close;

	depth_parenthesis = 0;
	lex_data = lexlst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		depth_parenthesis++;
	rear = lexlst;
	front = lexlst->next;
	while (front)
	{
		lex_data = front->content;
		if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
			depth_parenthesis++;
		else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		{
			depth_parenthesis--;
			if (depth_parenthesis == 0)
				last_close = rear;
		}
		rear = front;
		front = front->next;
	}
	return (last_close);
}

// static t_parse	*make_root_subshell(t_parse *subshell) // subshell이 중간노드가 된다
// {
// 	t_lex	*prev_parenthesis_close;
// 	t_lex	*subshell_open_token;
// 	t_lex	*after_parenthesis;

// 	prev_parenthesis_close = get_prev_last_parenthesis_close(subshell->node);
// 	after_parenthesis = prev_parenthesis_close->next->next;
// 	if (after_parenthesis)
// 	{
// 		subshell->right = ft_calloc(1, sizeof(t_parse));
// 		subshell->right->node = after_parenthesis;
// 	}
// 	ft_lstdelone(prev_parenthesis_close->next, free);
// 	prev_parenthesis_close->next = NULL;
// 	subshell_open_token = subshell->node;
// 	subshell->node = subshell_open_token->next;
// 	ft_lstdelone(subshell_open_token, free);
// 	subshell->left = parse(subshell->node);
// 	if (subshell->left == NULL)
// 		return (NULL);
// 	subshell->node = NULL;
// 	subshell->is_subshell = 1;
// 	return (subshell);
// }

static t_parse	*make_root_subshell(t_parse *subshell) // subshell이 중간노드가 된다
{
	t_parse	*root;
	t_lex	*prev_parenthesis_close;
	t_lex	*start_parenthesis;

	root = ft_calloc(1, sizeof(t_parse));
	prev_parenthesis_close = get_prev_last_parenthesis_close(subshell->node);
	ft_lstdelone(prev_parenthesis_close->next, free);
	prev_parenthesis_close->next = NULL;
	start_parenthesis = subshell->node;
	subshell->node = subshell->node->next;
	ft_lstdelone(start_parenthesis, free);
	root->left = subshell;
	root->is_subshell = 1;
	return (root);
}

int	has_parenthesis(t_lex *lexlst)
{
	int			dquote_flag;
	t_lexeme	*lex_data;

	dquote_flag = 0;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (1);
		lexlst = lexlst->next;
	}
	return (0);
}

t_lex	*get_next_lextoken_nonifs(t_lex *lexlst)
{
	t_lexeme	*lex_data;

	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type != LEXEME_IFS)
			break ;
		lexlst = lexlst->next;
	}
	return (lexlst);
}

void	remove_subs(t_parse *subshell_node)
{
	t_lex		*to_remove;

	to_remove = get_prev_last_parenthesis_close(subshell_node->node)->next;
	get_prev_last_parenthesis_close(subshell_node->node)->next = NULL;
	ft_lstdelone(to_remove, free);
	to_remove = subshell_node->node;
	subshell_node->node = subshell_node->node->next;
	ft_lstdelone(to_remove, free);
}

int	subshell_syntax_error(t_lex *lexlst)
{
	t_lexeme	*lex_data;
	int			redirection_flag;

	redirection_flag = 0;
	while (1)
	{
		lexlst = get_next_lextoken_nonifs(lexlst);
		if (lexlst == NULL)
			return (0);
		lex_data = lexlst->content;
		if (redirection_flag == 0)
		{
			if (lex_data->type != LEXEME_ADDFILE
				&& lex_data->type != LEXEME_HEREDOC
				&& lex_data->type != LEXEME_INFILE
				&& lex_data->type != LEXEME_OUTFILE)
				return (1);
		}
		else if (redirection_flag == 1)
		{
			if (lex_data->type != LEXEME_WILDCARD
				&& lex_data->type != LEXEME_DQUOTE
				&& lex_data->type != LEXEME_STRING)
				return (1);
		}
		lexlst = lexlst->next;
	}
}

int	make_leaf_subshell(t_parse *root)
{
	t_parse		*subshell_node;
	t_lexeme	*lex_data;

	if (root->left)
		return (make_leaf_subshell(root->left));
	else if (root->right)
		return (make_leaf_subshell(root->right));
	else if (has_parenthesis(root->node))
	{
		lex_data = root->node->content;
		if (lex_data->type != LEXEME_PARENTHESIS_OPEN) // syntax error
			return (1);
		subshell_node = ft_calloc(1, sizeof(t_parse));
		root->left = subshell_node;
		root->is_subshell = 1;
		subshell_node->node = root->node;
		root->node = get_prev_last_parenthesis_close(subshell_node->node)->next->next;
		get_prev_last_parenthesis_close(subshell_node->node)->next->next = NULL;
		remove_subs(subshell_node);
		if (subshell_syntax_error(root->node)) // syntax error
			return (1);
	}
	return (0);
}

t_parse	*parse(t_lex *lexlst)
{
	t_parse	*tree_operator;

	tree_operator = operator_parse(lexlst);
	if (tree_operator == NULL)
		return (NULL);
	while (is_root_subshell(lexlst))
		tree_operator = make_root_subshell(tree_operator);
	make_leaf_subshell(tree_operator);
	return (tree_operator);
}
