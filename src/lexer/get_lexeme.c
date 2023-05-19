/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexeme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:48:29 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 02:16:51 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"

enum e_lexeme	lexeme_type(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (LEXEME_EOF);
	return (((struct s_lexeme *)(curr->content))->type);
}

size_t	lexeme_len(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (0);
	return (((struct s_lexeme *)(curr->content))->len);
}

const char	*lexeme_data(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (NULL);
	return (((struct s_lexeme *)(curr->content))->data);
}

char	*lexeme_str(t_lex_lst *curr)
{
	struct s_lexeme	*content;

	if (curr == NULL || curr->content == NULL)
		return (NULL);
	content = curr->content;
	return (ft_strndup(content->data, content->len));
}
