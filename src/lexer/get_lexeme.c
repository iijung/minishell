/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexeme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:48:29 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/15 04:58:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"

enum e_lexeme	lexeme_type(void *param)
{
	if (param == NULL)
		return (LEXEME_EOF);
	return (((struct s_lexeme *)param)->type);
}

size_t	lexeme_len(void *param)
{
	if (param == NULL)
		return (0);
	return (((struct s_lexeme *)param)->len);
}

const char	*lexeme_data(void *param)
{
	if (param == NULL)
		return (NULL);
	return (((struct s_lexeme *)param)->data);
}

char	*lexeme_str(void *param)
{
	struct s_lexeme *const	content = param;

	if (param == NULL)
		return (NULL);
	return (ft_strndup(content->data, content->len));
}
