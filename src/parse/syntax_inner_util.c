/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_inner_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:25:43 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/16 15:30:38 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_redirection_lex(t_s_lex *lex_data)
{
	return (lex_data->type == LEXEME_ADDFILE
		|| lex_data->type == LEXEME_INFILE
		|| lex_data->type == LEXEME_HEREDOC
		|| lex_data->type == LEXEME_OUTFILE);
}

int	is_operator_lex(t_s_lex *lex_data)
{
	return (lex_data->type == LEXEME_PIPE
		|| lex_data->type == LEXEME_AND
		|| lex_data->type == LEXEME_OR);
}

int	is_about_string_lex(t_s_lex *lex_data)
{
	return (lex_data->type != LEXEME_STRING
		&& lex_data->type != LEXEME_WILDCARD
		&& lex_data->type != LEXEME_ENVIRONMENT);
}
