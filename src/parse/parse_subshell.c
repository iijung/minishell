/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:13:15 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 16:53:50 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	has_subshell(t_lex_lst *lexlst)
{
	t_s_lex	*lex_data;
	int		dquote_flag;

	dquote_flag = 0;
	while (lexlst)
	{
		if (lexlst->content)
			lex_data = lexlst->content;
		else
			break ;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (1);
		lexlst = lexlst->next;
	}	
	return (0);
}

static t_lex_lst	*get_prev_last_parenthesis_close(t_lex_lst *lexlst)
{
	t_lex_lst	*front;
	t_lex_lst	*rear;
	t_lex_lst	*last_close;
	t_s_lex		*lex_data;

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

t_lex_lst	*get_next_lextoken_nonifs(t_lex_lst *lexlst)
{
	t_lex_lst	*cur_lexlst;
	t_s_lex		*lex_data;

	cur_lexlst = lexlst;
	while (cur_lexlst)
	{
		lex_data = cur_lexlst->content;
		if (lex_data->type != LEXEME_IFS)
			break ;
		cur_lexlst = cur_lexlst->next;
	}
	lex_data = cur_lexlst->content;
	if (lex_data->type == LEXEME_EOF)
		return (lexlst);
	return (cur_lexlst);
}

static void	subshell_parse_process(\
	t_lex_lst **tmp_node, t_lex_lst *new_lst, t_parse *tree_operator)
{
	t_lex_lst	*redirection;
	t_lex_lst	*maybe_ifs;
	t_s_lex		*lex_data;

	maybe_ifs = (*tmp_node)->next;
	ft_lstdelone(*tmp_node, free);
	lex_data = maybe_ifs->content;
	if (lex_data->type == LEXEME_IFS)
		ft_lstdelone(maybe_ifs, free);
	*tmp_node = get_prev_last_parenthesis_close(new_lst);
	redirection = (*tmp_node)->next->next;
	ft_lstdelone((*tmp_node)->next, free);
	(*tmp_node)->next = NULL;
	tree_operator->node = redirection;
	tree_operator->is_subshell = 1;
	tree_operator->left = parse(new_lst);
}

t_parse	*subshell_parse(t_parse *tree_operator)
{
	t_lex_lst	*tmp_node;
	t_lex_lst	*new_lst;
	t_s_lex		*lex_data;

	if (tree_operator->node && tree_operator->node->content)
	{
		lex_data = get_next_lextoken_nonifs(tree_operator->node)->content;
	}
	else
		return (tree_operator);
	if (has_subshell(tree_operator->node) \
		&& lex_data->type == LEXEME_PARENTHESIS_OPEN)
	{
		tmp_node = get_next_lextoken_nonifs(tree_operator->node);
		new_lst = get_next_lextoken_nonifs(tmp_node->next);
		lex_data = new_lst->content;
		if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			return (tree_operator);
		subshell_parse_process(&tmp_node, new_lst, tree_operator);
	}
	if (tree_operator->left)
		tree_operator->left = subshell_parse(tree_operator->left);
	if (tree_operator->right)
		tree_operator->right = subshell_parse(tree_operator->right);
	return (tree_operator);
}