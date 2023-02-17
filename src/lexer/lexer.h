/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:21:00 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/17 19:27:29 by minjungk         ###   ########.fr       */
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
	LEXEME_WILDCARD,
	LEXEME_ENVIRONMENT,
	LEXEME_PARENTHESIS,
	LEXEME_OR,
	LEXEME_AND,
	LEXEME_PIPE,
	LEXEME_HEREDOC,
	LEXEME_INFILE,
	LEXEME_OUTFILE,
	LEXEME_ADDFILE
};

struct s_content
{
	int			type;
	size_t		len;
	const char	*data;
};

t_list	*lex(char *command);

#endif
