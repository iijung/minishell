/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_getter2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:36:56 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/22 22:52:52 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

static int	is_or_and_lex(t_s_lex *lex_data)
{
	return (lex_data->type == LEXEME_AND || lex_data->type == LEXEME_OR);
}

t_lex_lst	*get_last_operator_node(t_lex_lst *token_lst)
{
	int			dquote_flag;
	int			subshell_depth;
	t_s_lex		*lex_data;
	t_lex_lst	*last;

	dquote_flag = 0;
	subshell_depth = 0;
	last = NULL;
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
			else if (subshell_depth == 0 && is_or_and_lex(lex_data))
				last = token_lst;
		}
		token_lst = token_lst->next;
	}
	return (last);
}
