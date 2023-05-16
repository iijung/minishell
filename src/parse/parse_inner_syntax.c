/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:56:15 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/14 16:17:58 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "parse_inner_util.h"

int	check_quote_parenthesis_match_error(t_list *token)
{
	int	dquote_flag;
	int	parenthesis_dep;

	dquote_flag = 0;
	parenthesis_dep = 0;
	loop_check_match(token, &dquote_flag, &parenthesis_dep);
	if (dquote_flag == 0 && parenthesis_dep == 0)
		return (0);
	else
		return (1);
}

int	check_empty_subshell(t_lex_lst *lexlst)
{
	t_s_lex	*front_lex_data;
	t_s_lex	*rear_lex_data;

	while (lexlst && lexlst->next)
	{
		rear_lex_data = lexlst->content;
		front_lex_data = lexlst->next->content;
		if (rear_lex_data->type == LEXEME_PARENTHESIS_OPEN
			&& front_lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			return (1);
		lexlst = lexlst->next;
	}
	return (0);
}

void	loop_check_match(
	t_list *token,
	int *dquote_flag,
	int *parenthesis_dep
)
{
	t_s_lex	*cur_token_data;

	while (token)
	{
		cur_token_data = token->content;
		if (cur_token_data->type == LEXEME_DQUOTE)
			*dquote_flag ^= 1;
		else if ((cur_token_data->type == LEXEME_PARENTHESIS_OPEN || \
				cur_token_data->type == LEXEME_PARENTHESIS_CLOSE) && \
				*dquote_flag == 0)
		{
			if (cur_token_data->type == LEXEME_PARENTHESIS_OPEN)
				(*parenthesis_dep)++;
			else
				(*parenthesis_dep)--;
		}
		token = token->next;
	}
}
