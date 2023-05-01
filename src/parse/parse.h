/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:27:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/01 16:35:27 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "lexer.h"

typedef struct s_parse
{
	struct s_lexeme	*left;
	struct s_lexeme	*right;
	t_list			*token;
}	t_parse;

#endif