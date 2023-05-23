/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:05:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 18:30:10 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_lex_lst	*_str(t_env **table, t_lex_lst *curr, char **dst)
{
	char			*key;
	char			*val;
	const t_e_lex	type = lexeme_type(curr);

	key = lexeme_str(curr);
	if (type == LEXEME_ENVIRONMENT)
	{
		val = env_get_val(table, key);
		if (val)
		{
			val = ft_strjoin(*dst, val);
			ft_assert(val == NULL, __FILE__, __LINE__);
			free(*dst);
			*dst = val;
		}
	}
	else
	{
		val = ft_strjoin(*dst, key);
		ft_assert(val == NULL, __FILE__, __LINE__);
		free(*dst);
		*dst = val;
	}
	free(key);
	return (curr->next);
}

t_lex_lst	*combine_string(t_env **table, t_lex_lst *curr, char **dst)
{
	if (curr == NULL || dst == NULL)
		return (curr);
	if (*dst == NULL)
		*dst = ft_strdup("");
	if (*dst == NULL)
		return (NULL);
	while (curr)
	{
		if (lexeme_type(curr) != LEXEME_STRING
			&& lexeme_type(curr) != LEXEME_DQUOTE
			&& lexeme_type(curr) != LEXEME_ENVIRONMENT
			&& lexeme_type(curr) != LEXEME_WILDCARD)
			break ;
		if (lexeme_type(curr) == LEXEME_DQUOTE)
		{
			curr = curr->next;
			while (lexeme_type(curr) != LEXEME_DQUOTE)
				curr = _str(table, curr, dst);
			curr = curr->next;
		}
		else
			curr = _str(table, curr, dst);
	}
	return (curr);
}
