/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:13:34 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/04/11 20:26:21 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

enum
{
	LEXEME_AND,
	LEXEME_OR,
	LEXEME_SUB_S,
	LEXEME_SUB_E,
	LEXEME_PIPE,
	LEXEME_STRING,
	LEXEME_READ,
	LEXEME_HEREDOC,
	LEXEME_WRITE,
	LEXEME_APPEND,
	LEXEME_END = 10,
	LEXEME_DQUOTE,
	LEXEME_SQUOTE,
	LEXEME_IFS = 13,
	LEXEME_WORD,
	LEXEME_ERROR
};

enum
{
	E_READ_STRING_NORM = 1 << 0,
	E_READ_STRING_IN_DQUOTE = 1 << 1,
	E_READ_STRING_IN_SQUOTE = 1 << 2,
	E_READ_STRING_ACC = 1 << 3,
	E_READ_STRING_ERROR = 1 << 4
};

typedef struct s_lex_token
{
	char				*string;
	struct s_lex_token	*next;
	void				*byte_pedding[2];
	unsigned int		type;
}	t_lex_token;

t_lex_token	*lexer(const char *input);

#endif
