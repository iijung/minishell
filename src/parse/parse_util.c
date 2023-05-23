/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:44:34 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/21 00:57:10 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	clear_parse_tree(t_parse *root, void (*f)(void *))
{
	if (root == NULL)
		return ;
	clear_parse_tree(root->left, f);
	clear_parse_tree(root->right, f);
	ft_lstclear(&root->node, f);
	free(root);
}

void	debug_print_parse_tree(t_parse *parse_tree)
{
	if (parse_tree == NULL)
		return ;
	if (parse_tree->is_subshell)
		printf("this is SUBSHELL_NODE\n");
	ft_lstiter(parse_tree->node, lexeme_debug);
	debug_print_parse_tree(parse_tree->left);
	debug_print_parse_tree(parse_tree->right);
}
