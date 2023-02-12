/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:21:00 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/12 15:04:00 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include <stdio.h>

enum e_lexeme
{
	LEXEME_STRING,
	LEXEME_EOF,
	LEXEME_IFS,
	LEXEME_QUOTE,
	LEXEME_DQUOTE,
	LEXEME_OPERATOR,
	LEXEME_WILDCARD,
	LEXEME_ENVIRONMENT,
	LEXEME_PARENTHESIS,
	LEXEME_REDIRECTION
};

struct s_content
{
	int		type;
	size_t	len;
	char	*data;
};

t_list	*lex(char *command);

#endif
