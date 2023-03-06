/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:13:34 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 05:15:36 by jaemjeon         ###   ########.fr       */
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
int			is_ifs(char c);
int			is_meta(const char *string);
int			set_read_string_state(char c);
int			get_next_type(const char *input);
void		skip_ifs(const char **string);

#endif
