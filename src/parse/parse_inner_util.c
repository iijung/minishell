/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:49:14 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/17 08:53:07 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	has_subshell(t_lex_lst *token_lst)
{
	int			dquote_flag;
	t_s_lex		*lex_data;

	dquote_flag = 0;
	while (token_lst)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
				return (1);
		}
		token_lst = token_lst->next;
	}
	return (0);
}

static int	delete_first_case(t_lex_lst **start)
{
	t_s_lex		*first_lex_data;
	t_s_lex		*second_lex_data;
	t_lex_lst	*to_delete;

	first_lex_data = (*start)->content;
	if (first_lex_data->type == LEXEME_DQUOTE)
		return (1);
	second_lex_data = (*start)->next->content;
	if (is_ifs_token(*start) && !is_about_string_token((*start)->next))
	{
		to_delete = *start;
		*start = (*start)->next;
		ft_lstdelone(to_delete, free);
	}
	else if (!is_about_string_token(*start) && is_ifs_token((*start)->next))
	{
		to_delete = (*start)->next;
		(*start)->next = (*start)->next->next;
		ft_lstdelone(to_delete, free);
	}
	return (0);
}

static void	delete_next_token(t_lex_lst *before_delete)
{
	t_lex_lst	*to_delete;

	to_delete = before_delete->next;
	before_delete->next = before_delete->next->next;
	ft_lstdelone(to_delete, free);
}

void	delete_useless_ifs(t_lex_lst *start)
{
	int			dquote_flag;
	t_s_lex		*lex_data;
	t_lex_lst	*to_delete;

	if (ft_lstsize(start) < 3)
		return ;
	dquote_flag = delete_first_case(&start);
	while (start->next->next)
	{
		lex_data = start->next->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (is_ifs_token(start->next)
				&& !is_about_string_token(start->next->next))
				delete_next_token(start);
			else if (!is_about_string_token(start->next)
				&& is_ifs_token(start->next->next))
				delete_next_token(start);
		}
		start = start->next;
	}
}
