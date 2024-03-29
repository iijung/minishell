/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/21 14:11:59 by jaemjeon         ###   ########.fr       */
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
	t_lex_lst		*node;
}	t_parse;

// parse.c
t_parse	*parse(t_lex_lst *token_lst);
void	delete_useless_ifs(t_lex_lst *start);

// parse_util.c
void	debug_print_parse_tree(t_parse *parse_tree);
void	clear_parse_tree(t_parse *root, void (*f)(void*));

// syntax.c
int		is_syntax_error(t_parse *root);
#endif
