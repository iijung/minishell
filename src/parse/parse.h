/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/16 11:50:32 by jaemjeon         ###   ########.fr       */
=======
/*   Updated: 2023/05/14 16:13:59 by jaemjeon         ###   ########.fr       */
>>>>>>> faa363bfb476eb5d3914f2095fb23c98eaa29aa9
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
t_parse	*parse(t_lex_lst *token_lst);

// parse_util.c
void	debug_print_parse_tree(t_parse *parse_tree);
void	clear_parse_tree(t_parse *root, void (*f)(void*));

// syntax.c
int		is_syntax_error(t_parse *root);
#endif
