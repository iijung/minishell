/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:49:14 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/14 16:33:02 by jaemjeon         ###   ########.fr       */
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

int	is_about_string_token(t_lex_lst *token)
{
	const t_s_lex	*lex_data = token->content;

	return (lex_data->type == LEXEME_STRING
		|| lex_data->type == LEXEME_ENVIRONMENT
		|| lex_data->type == LEXEME_WILDCARD
		|| lex_data->type == LEXEME_DQUOTE);
}

int	is_ifs_token(t_lex_lst *token)
{
	const t_s_lex	*lex_data = token->content;

	return (lex_data->type == LEXEME_IFS);
}

/*
size of rear is more than 2.
this function do not check the list size
*/
void	delete_useless_ifs(t_lex_lst *rear)
{
	t_lex_lst	*front;
	t_lex_lst	*to_delete;

	front = rear->next->next;
	while (front)
	{
		if (!is_about_string_token(rear->next) && is_ifs_token(front))
		{
			to_delete = front;
			front = front->next;
			rear->next->next = front;
			ft_lstdelone(to_delete, free);
			rear = rear->next;
			continue ;
		}
		else if (is_ifs_token(rear->next) && !is_about_string_token(front))
		{
			ft_lstdelone(rear->next, free);
			rear->next = front;
			front = front->next;
			continue ;
		}
		front = front->next;
		rear = rear->next;
	}
}
