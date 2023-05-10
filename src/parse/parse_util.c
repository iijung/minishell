/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:56:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/11 00:17:28 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

t_lex_lst	*make_new_lexlst(t_lex_lst *start, t_lex_lst *end)
{
	t_lex_lst	*new_lexlst;
	t_lex_lst	*lex_loop;

	if (start == NULL || end == NULL)
		return (NULL);
	new_lexlst = NULL;
	lex_loop = start;
	while (lex_loop != end)
	{
		ft_lstadd_back(&new_lexlst, ft_lstnew(lex_loop->content));
		lex_loop = lex_loop->next;
	}
	ft_lstadd_back(&new_lexlst, ft_lstnew(lex_loop->content));
	return (new_lexlst);
}

t_parse	*make_new_node(t_lex_lst *start, t_lex_lst *end)
{
	t_parse		*node;

	node = ft_calloc(1, sizeof(t_parse));
	node->node = make_new_lexlst(start, end);
	return (node);
}