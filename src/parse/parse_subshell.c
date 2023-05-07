/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:13:15 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/07 18:26:18 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

static void	lexlst_del(t_lex *from, t_lex *destination)
{
	while (from != destination)
	{
		ft_lstdelone(from, free);
		from = from->next;
	}
}

t_parse	*subshell_parse(t_parse *tree_operator)
{
	t_lex		*tmp_node;
	t_lex		*new_lst;
	t_lex		*redirection;
	t_lexeme	*lex_data;

	lex_data = tree_operator->node->content;
	if (has_subshell(tree_operator->node) \
		&& lex_data->type == LEXEME_PARENTHESIS_OPEN)
	{
		tmp_node = tree_operator->node;
		new_lst = get_next_lextoken_nonifs(tmp_node->next);
		lexlst_del(tmp_node, new_lst);
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
