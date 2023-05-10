/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:56:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 19:02:52 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

t_parse	*make_new_node(t_lex_lst *start, t_lex_lst *end)
{
	t_parse		*node;
	t_lex_lst	*lex_loop;

	node = ft_calloc(1, sizeof(t_parse));
	lex_loop = start;
	while (lex_loop != end)
	{
		ft_lstadd_back(&(node->node), ft_lstnew(lex_loop->content));
		lex_loop = lex_loop->next;
	}
	ft_lstadd_back(&(node->node), ft_lstnew(lex_loop->content));
	return (node);
}