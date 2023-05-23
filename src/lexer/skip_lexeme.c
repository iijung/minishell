/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_lexeme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:52:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/14 19:55:00 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex_lst	*skip_lexeme_ifs(t_lex_lst *curr)
{
	struct s_lexeme	*content;

	if (curr == NULL || curr->content == NULL)
		return (curr);
	while (curr && curr->content)
	{
		content = curr->content;
		if (content->type != LEXEME_IFS)
			return (curr);
		curr = curr->next;
	}
	return (curr);
}
