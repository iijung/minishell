/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_inner_util.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:26:29 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/16 15:27:41 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_INNER_UTIL_H
# define SYNTAX_INNER_UTIL_H
# include "lexer.h"

int	is_redirection_lex(t_s_lex *lex_data);
int	is_operator_lex(t_s_lex *lex_data);
int	is_about_string_lex(t_s_lex *lex_data);

#endif
