/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/11 00:29:04 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "lexer.h"

typedef struct s_parse
{
	struct s_parse	*left;
	struct s_parse	*right;
	int				is_subshell;
	t_list			*node;
}	t_parse;

// parse.c
t_parse		*parse(t_lex_lst *tokens);
void		debug_print_parse_tree(t_parse *parse_tree);
void		clear_parse_tree(t_parse *root, void(*f)(void*));

// parse_util.c
t_parse	*make_new_node(t_lex_lst *start, t_lex_lst *end);
t_lex_lst	*make_new_lexlst(t_lex_lst *start, t_lex_lst *end);
t_parse	*expand_subshell(t_parse *root);

// parse_operator.c
t_parse	*split_with_operator(t_lex_lst *start, t_lex_lst *end);

// parse_subshell.c
t_parse	*expand_subshell(t_parse *root);

#endif
