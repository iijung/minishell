/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:55:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/12 15:28:00 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

int	has_something_before_parenthesis(t_lex_lst *lexlst)
{
	t_s_lex		*lex_data;

	lex_data = lexlst->content;
	// if (lex_data->type == LEXEME_IFS)
	// 	lexlst = lexlst->next;
	lex_data = lexlst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		return (0);
	return (1);
}

t_lex_lst	*get_something_before_parenthesis(t_lex_lst **lexlst)
{
	t_lex_lst	*start_lexlst;
	t_lex_lst	*end_of_something;
	t_s_lex		*lex_data;

	start_lexlst = *lexlst;
	while (1)
	{
		lex_data = (*lexlst)->next->content;
		if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		{
			end_of_something = *lexlst;
			break ;
		}
		(*lexlst) = (*lexlst)->next;
	}
	(*lexlst) = (*lexlst)->next;
	end_of_something->next = NULL;
	return (start_lexlst);
}

t_lex_lst	*find_first_parenthesis_open(t_lex_lst *lexlst)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (lexlst);
		lexlst = lexlst->next;
	}
	return (NULL);
}

t_lex_lst	*find_before_last_parenthesis_close(t_lex_lst *lexlst)
{
	t_lex_lst	*last_before_last;
	t_lex_lst	*prev_lexlst;
	t_s_lex		*lex_data;
	int			dquote_flag;

	dquote_flag = 0;
	last_before_last = lexlst;
	lex_data = last_before_last->next->content;
	if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		return (last_before_last);
	lexlst = lexlst->next;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			last_before_last = prev_lexlst;
		prev_lexlst = lexlst;
		lexlst = lexlst->next;
	}
	return (last_before_last);
}

t_parse	*get_something_after_parenthesis(t_lex_lst **lexlst)
{
	t_parse		*node;
	t_lex_lst	*before_last_parenthesis_close;
	t_lex_lst	*something;

	before_last_parenthesis_close = find_before_last_parenthesis_close(*lexlst);
	something = before_last_parenthesis_close->next->next;
	node = make_new_node(something, ft_lstlast(something));
	return (node);
}

int	has_subshell(t_lex_lst *lexlst)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

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

int	has_something_after_parenthesis(t_lex_lst *lexlst)
{
	t_lex_lst	*after_parenthesis;
	t_s_lex		*lex_data;	

	after_parenthesis = (find_before_last_parenthesis_close(lexlst))->next->next;
	if (after_parenthesis == NULL)
		return (0);
	lex_data = after_parenthesis->content;
	if (lex_data->type == LEXEME_IFS && after_parenthesis->next == NULL)
		return (0);
	else
		return (1);
}

void	expand_inner_subshell(t_parse *root)
{
	t_parse	*new_root;

	if (root->left && root->left->node)
	{
		new_root = split_with_operator(root->left->node, ft_lstlast(root->left->node));
		clear_parse_tree(root->left, NULL);
		free(root->left);
		root->left = new_root;
	}
	if (root->right && root->right ->node)
	{
		new_root = split_with_operator(root->right->node, ft_lstlast(root->right->node));
		clear_parse_tree(root->right, NULL);
		free(root->right);
		root->right = new_root;
	}
	if (root->left && root->left->node && has_subshell(root->left->node))
		root->left = expand_root_subshell(root->left);
	if (root->right && root->right->node && has_subshell(root->right->node))
		root->right = expand_root_subshell(root->right);
}

t_lex_lst *get_inner_subshell(t_lex_lst *subshell_lst)
{
	t_lex_lst	*subshell_open;
	t_lex_lst	*after_subshell_open;
	t_lex_lst	*before_subshell_close;

	subshell_open = find_first_parenthesis_open(subshell_lst);
	after_subshell_open = subshell_open->next;
	before_subshell_close = find_before_last_parenthesis_close(subshell_lst);
	subshell_open->next = before_subshell_close->next;
	before_subshell_close->next = NULL;
	return (after_subshell_open);
}

t_parse	*expand_root_subshell(t_parse *root)
{
	t_parse		*new_root;
	t_lex_lst	*inner_lexlst;
	t_s_lex		*lex_data;

	lex_data = root->node->content;
	expand_inner_subshell(root);
	if (!has_subshell(root->node))
		return (root);
	new_root = ft_calloc(1, sizeof(t_parse));
	new_root->is_subshell = 1;
	if (has_something_before_parenthesis(root->node))
		new_root->node = get_something_before_parenthesis(&(root->node));
	if (has_something_after_parenthesis(root->node))
		new_root->right = get_something_after_parenthesis(&(root->node));
	inner_lexlst = get_inner_subshell(root->node);
	ft_lstclear(&(root->node), free);
	free(root);
	new_root->left = parse(inner_lexlst);
	ft_lstclear(&inner_lexlst, NULL);
	return (new_root);
}
