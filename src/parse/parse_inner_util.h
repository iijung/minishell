/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_util.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:46:32 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/22 21:43:23 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INNER_UTIL_H
# define PARSE_INNER_UTIL_H
# include "lexer.h"

// parse_inner_util.c
extern int	has_subshell(t_lex_lst *curr);
int			is_about_string_token(t_lex_lst *token);
int			is_ifs_token(t_lex_lst *token);
void		delete_useless_ifs(t_lex_lst *rear);

// parse_inner_util2.c
t_lex_lst	*make_new_token_lst(t_lex_lst *start, t_lex_lst *end);
t_parse		*make_new_node(t_lex_lst *token_lst);

// parse_inner_getter.c
t_lex_lst	*get_left_start(t_lex_lst *start, t_lex_lst *root);
t_lex_lst	*get_right_start(t_lex_lst *root);
t_lex_lst	*get_before_first_subshell_open(
				t_lex_lst *token_lst,
				t_lex_lst **first_open
				);
t_lex_lst	*get_before_last_subshell_close(t_lex_lst *token_lst);

// parse_inner_getter2.c
t_lex_lst	*get_type_node(t_lex_lst *token_lst, t_e_lex type);
t_lex_lst	*get_last_operator_node(t_lex_lst *token_lst);

// parse_inner_syntax.c
extern int	check_inner_syntax(t_lex_lst *curr);

#endif
