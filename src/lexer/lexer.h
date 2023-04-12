/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:21:00 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/12 21:22:55 by minjungk         ###   ########.fr       */
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
	LEXEME_OR,
	LEXEME_AND,
	LEXEME_HEREDOC,
	LEXEME_ADDFILE,
	LEXEME_OUTFILE,
	LEXEME_INFILE,
	LEXEME_PIPE,
	LEXEME_QUOTE,
	LEXEME_DQUOTE,
	LEXEME_WILDCARD,
	LEXEME_ENVIRONMENT,
	LEXEME_PARENTHESIS_OPEN,
	LEXEME_PARENTHESIS_CLOSE,
	MAX_LEXEME
};

struct s_lexeme
{
	enum e_lexeme	type;
	size_t			len;
	const char		*data;
};

static const struct s_lexeme	g_lexeme[] = {
[LEXEME_STRING] = {LEXEME_STRING, 0, NULL},
[LEXEME_EOF] = {LEXEME_EOF, 0, NULL},
[LEXEME_IFS] = {LEXEME_IFS, 0, NULL},
[LEXEME_OR] = {LEXEME_OR, 2, "||"},
[LEXEME_AND] = {LEXEME_AND, 2, "&&"},
[LEXEME_HEREDOC] = {LEXEME_HEREDOC, 2, "<<"},
[LEXEME_ADDFILE] = {LEXEME_ADDFILE, 2, ">>"},
[LEXEME_OUTFILE] = {LEXEME_OUTFILE, 1, ">"},
[LEXEME_INFILE] = {LEXEME_INFILE, 1, "<"},
[LEXEME_PIPE] = {LEXEME_PIPE, 1, "|"},
[LEXEME_QUOTE] = {LEXEME_QUOTE, 1, "\'"},
[LEXEME_DQUOTE] = {LEXEME_DQUOTE, 1, "\""},
[LEXEME_WILDCARD] = {LEXEME_WILDCARD, 1, "*"},
[LEXEME_ENVIRONMENT] = {LEXEME_ENVIRONMENT, 1, "$"},
[LEXEME_PARENTHESIS_OPEN] = {LEXEME_PARENTHESIS_OPEN, 1, "("},
[LEXEME_PARENTHESIS_CLOSE] = {LEXEME_PARENTHESIS_CLOSE, 1, ")"}};

t_list	*lex(char *command);

#endif
