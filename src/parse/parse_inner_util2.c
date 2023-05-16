/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inner_util2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:04:02 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/14 16:11:05 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_lex_lst	*make_new_token_lst(t_lex_lst *start, t_lex_lst *end)
{
	t_lex_lst	*new_token_lst;

	new_token_lst = NULL;
	if (start == NULL || end == NULL)
		return (NULL);
	while (start != end)
	{
		ft_lstadd_back(&new_token_lst, ft_lstnew(start->content));
		start = start->next;
	}
	ft_lstadd_back(&new_token_lst, ft_lstnew(start->content));
	return (new_token_lst);
}

t_parse	*make_new_node(t_lex_lst *token_lst)
{
	t_parse	*root;

	if (token_lst == NULL)
		return (NULL);
	root = ft_calloc(1, sizeof(t_parse));
	if (root == NULL)
		return (NULL);
	root->node = token_lst;
	return (root);
}
