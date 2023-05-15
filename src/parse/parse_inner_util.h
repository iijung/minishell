/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_util.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:46:32 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/14 16:17:11 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INNER_UTIL_H
# define PARSE_INNER_UTIL_H

typedef struct s_list	t_list;
typedef t_list			t_lex_lst;
typedef enum e_lexeme	t_e_lex;

// parse_inner_util.c
int			has_subshell(t_lex_lst *token_lst);
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
t_lex_lst	*get_type_node(t_lex_lst *token_lst, t_e_lex type);

// parse_inner_syntax.c
int			check_quote_parenthesis_match_error(t_list *token);
int			check_empty_subshell(t_lex_lst *lexlst);
void		loop_check_match(
				t_list *token,
				int *dquote_flag,
				int *parenthesis_dep);

#endif
