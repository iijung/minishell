/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:13:34 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 04:27:28 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

enum
{
	E_AND,
	E_OR,
	E_SUB_S,
	E_SUB_E,
	E_PIPE,
	E_STRING,
	E_READ,
	E_HEREDOC,
	E_WRITE,
	E_APPEND,
	E_END = 10,
	E_DQUOTE,
	E_SQUOTE,
	E_IFS = 13,
	E_WORD,
	E_ERROR
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
int	is_ifs(char c);
int	is_meta(const char *string);
int	set_read_string_state(char c);
int	get_next_type(const char *input);
void	skip_ifs(const char **string);

#endif
