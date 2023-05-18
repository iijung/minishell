/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:52:06 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/18 23:24:35 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*make_join_free1(const char *s1, const char *s2)
{
	char		*rtn;
	const int	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;

	rtn = ft_calloc(dstsize, 1);
	ft_strlcpy(rtn, s1, dstsize);
	ft_strlcpy(rtn + ft_strlen(s1), s2, dstsize);
	free((void *)s1);
	return (rtn);
}

char	*read_string_sequence(t_lex_lst **curr)
{
	char	*rtn;
	int		dquote_flag;

	rtn = ft_strdup("");
	dquote_flag = 0;
	while (*curr)
	{
		if (((t_s_lex *)(*curr)->content)->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 1)
			rtn = make_join_free1(rtn, ((t_s_lex *)(*curr)->content)->data);
		else
		{
			if (((t_s_lex *)(*curr)->content)->type == LEXEME_IFS)
				return (rtn);
			else
				rtn = make_join_free1(rtn, ((t_s_lex *)(*curr)->content)->data);
		}
		*curr = (*curr)->next;
	}
	return (rtn);
}
