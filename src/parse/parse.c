/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/07 17:32:16 by jaemjeon         ###   ########.fr       */
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

static int	has_subshell(t_lex *lexlst)
{
	t_lexeme	*lex_data;
	int			dquote_flag;

	dquote_flag = 0;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (1);
		lexlst = lexlst->next;
	}	
	return (0);
}

static t_lex	*get_prev_last_parenthesis_close(t_lex *lexlst)
{
	t_lex		*front;
	t_lex		*rear;
	t_lex		*last_close;
	t_lexeme	*lex_data;

	last_close = NULL;
	lex_data = lexlst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		last_close = lexlst;
	front = lexlst->next;
	rear = lexlst;
	while (front)
	{
		lex_data = front->content;
		if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		last_close = rear;
		rear = front;
		front = front->next;
	}
	return (last_close);
}

static t_lex	*get_next_lextoken_nonifs(t_lex *lexlst)
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

static t_parse	*subshell_parse(t_parse *tree_operator)
{
	t_lex		*tmp_node;
	t_lex		*new_lst;
	t_lex		*redirection;
	t_lexeme	*lex_data;

	lex_data = tree_operator->node->content;
	if (has_subshell(tree_operator->node) && lex_data->type == LEXEME_PARENTHESIS_OPEN)
	{
		tmp_node = tree_operator->node;
		new_lst = get_next_lextoken_nonifs(tmp_node->next);
		while (tmp_node != new_lst)
		{
			ft_lstdelone(tmp_node, free);
			tmp_node = tmp_node->next;
		}
		tmp_node = get_prev_last_parenthesis_close(new_lst);
		redirection = tmp_node->next->next;
		ft_lstdelone(tmp_node->next, free);
		tmp_node->next = NULL;
		tree_operator->node = redirection;
		tree_operator->is_subshell = 1;
		tree_operator->left = parse(new_lst);
	}
	if (tree_operator->left)
		tree_operator->left = subshell_parse(tree_operator->left);
	if (tree_operator->right)
		tree_operator->right = subshell_parse(tree_operator->right);
	return (tree_operator);
}

t_parse	*parse(t_lex *lexlst)
{
	t_parse	*tree_operator;
	t_parse	*parse_tree;

	tree_operator = operator_parse(lexlst);
	if (tree_operator == NULL)
		return (NULL);
	parse_tree = subshell_parse(tree_operator);
	return (parse_tree);
}
