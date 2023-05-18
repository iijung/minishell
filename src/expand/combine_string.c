/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_lexeme.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:05:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 00:47:14 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_lex_lst	*_str(t_lex_lst *curr, char **dst, char *src)
{
	char	*tmp;

	if (src == NULL)
		return (curr);
	tmp = ft_strjoin(*dst, src);
	ft_assert(tmp == NULL, __FILE__, __LINE__);
	free(*dst);
	*dst = tmp;
	return (curr->next);
}

static t_lex_lst	*_dquote(t_env **table, t_lex_lst *curr, char **dst)
{
	char	*tmp;

	curr = curr->next;
	while (curr && lexeme_type(curr->content) != LEXEME_DQUOTE)
	{
		tmp = lexeme_str(curr->content);
		ft_assert(tmp == NULL, __FILE__, __LINE__);
		if (lexeme_type(curr->content) == LEXEME_ENVIRONMENT)
			curr = _str(curr, dst, env_get_val(table, tmp));
		else
			curr = _str(curr, dst, tmp);
		free(tmp);
	}
	return (curr->next);
}

t_lex_lst	*combine_string(t_env **table, t_lex_lst *curr, char **dst)
{
	char	*tmp;

	if (curr == NULL || dst == NULL)
		return (curr);
	if (*dst == NULL)
		*dst = ft_strdup("");
	if (*dst == NULL)
		return (NULL);
	while (curr)
	{
		if (lexeme_type(curr->content) != LEXEME_STRING
			&& lexeme_type(curr->content) != LEXEME_DQUOTE)
			break ;
		if (lexeme_type(curr->content) == LEXEME_DQUOTE)
			curr = _dquote(table, curr, dst);
		else
		{
			tmp = lexeme_str(curr->content);
			curr = _str(curr, dst, tmp);
			free(tmp);
		}
	}
	return (curr);
}

