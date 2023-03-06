/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 03:10:58 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 04:30:03 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_nonterminal_node(t_parse_tree *node)
{
	return (node->type >> 8);
}

void	clear_parse_tree(t_parse_tree *tree)
{
	if (tree == NULL)
		return ;
	clear_parse_tree(tree->child[0]);
	clear_parse_tree(tree->child[1]);
	clear_parse_tree(tree->child[2]);
	if (is_nonterminal_node(tree))
		free(tree);
}