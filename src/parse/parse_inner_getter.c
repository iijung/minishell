/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_getter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:53:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/14 15:55:30 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_lex_lst	*get_left_start(t_lex_lst *start, t_lex_lst *root)
{
	t_lex_lst	*left_start;

	left_start = start;
	while (start->next)
	{
		if (start->next == root)
		{
			start->next = NULL;
			return (left_start);
		}
		start = start->next;
	}
	return (left_start);
}

t_lex_lst	*get_right_start(t_lex_lst *root)
{
	t_lex_lst	*right_start;

	right_start = root->next;
	root->next = NULL;
	return (right_start);
}

t_lex_lst	*get_before_first_subshell_open(
	t_lex_lst *token_lst,
	t_lex_lst **first_open
)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	lex_data = token_lst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
	{
		*first_open = token_lst;
		return (NULL);
	}
	while (token_lst->next)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
		{
			*first_open = token_lst->next;
			return (token_lst);
		}
		token_lst = token_lst->next;
	}
	return (NULL);
}

t_lex_lst	*get_before_last_subshell_close(t_lex_lst *token_lst)
{
	int			dquote_flag;
	t_s_lex		*lex_data;
	t_lex_lst	*last_before_close;

	dquote_flag = 0;
	while (token_lst->next)
	{
		lex_data = token_lst->next->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			last_before_close = token_lst;
		token_lst = token_lst->next;
	}
	return (last_before_close);
}

t_lex_lst	*get_type_node(t_lex_lst *token_lst, t_e_lex type)
{
	int		dquote_flag;
	int		subshell_depth;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	subshell_depth = 0;
	while (token_lst)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
				subshell_depth++;
			else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
				subshell_depth--;
			else if (subshell_depth == 0 && lex_data->type == type)
				return (token_lst);
		}
		token_lst = token_lst->next;
	}
	return (NULL);
}
