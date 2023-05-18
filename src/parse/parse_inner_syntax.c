/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:56:15 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/19 02:20:14 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_quote_parenthesis_match_error(t_lex_lst *curr)
{
	int				dquote_flag;
	int				parenthesis_dep;
	enum e_lexeme	type;

	dquote_flag = 0;
	parenthesis_dep = 0;
	while (curr)
	{
		type = lexeme_type(curr);
		if (type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		if (dquote_flag == 0 && type == LEXEME_PARENTHESIS_OPEN)
			parenthesis_dep++;
		if (dquote_flag == 0 && type == LEXEME_PARENTHESIS_CLOSE)
			parenthesis_dep--;
		curr = curr->next;
	}
	return (dquote_flag || parenthesis_dep);
}

static int	check_empty_subshell(t_lex_lst *curr)
{
	t_s_lex	*front_lex_data;
	t_s_lex	*rear_lex_data;

	while (curr && curr->next)
	{
		rear_lex_data = curr->content;
		front_lex_data = curr->next->content;
		if (rear_lex_data->type == LEXEME_PARENTHESIS_OPEN
			&& front_lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	check_inner_syntax(t_lex_lst *curr)
{
	if (check_quote_parenthesis_match_error(curr))
		return (1);
	if (check_empty_subshell(curr))
		return (1);
	return (0);
}
