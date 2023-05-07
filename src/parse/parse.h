/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/07 18:17:27 by jaemjeon         ###   ########.fr       */
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

t_parse	*parse(t_lex *tokens);
void	debug_print_parse_tree(t_parse *parse_tree);
void	clear_parse_tree(t_parse *root);

// parse_subshell.c
t_parse	*subshell_parse(t_parse *tree_operator);
t_parse	*operator_parse(t_lex *lexlst);

#endif
