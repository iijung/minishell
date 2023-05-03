/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/03 10:32:18 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "lexer.h"

typedef struct s_parse
{
	struct s_parse	*left;
	struct s_parse	*right;
	t_list			*token;
}	t_parse;

t_parse	*parse(t_list *tokens);
void	debug_print_parse_tree(t_parse *parse_tree);

#endif