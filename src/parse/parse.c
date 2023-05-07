/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/07 18:18:16 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

void	clear_parse_tree(t_parse *root)
{
	t_parse	*left_tree;
	t_parse	*right_tree;

	left_tree = root->left;
	right_tree = root->right;
	if (left_tree)
	{
		clear_parse_tree(left_tree);
		free(left_tree);
	}
	if (right_tree)
	{
		clear_parse_tree(right_tree);
		free(right_tree);
	}
	ft_lstclear(&root->node, free);
}

void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	if (parse_tree->is_subshell)
		printf("this is SUBSHELL_NODE\n");
	ft_lstiter(parse_tree->node, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

t_parse	*parse(t_lex *lexlst)
{
	t_parse	*tree_operator;
	t_parse	*parse_tree;

	tree_operator = operator_parse(lexlst);
	if (tree_operator == NULL)
		return (NULL);
	parse_tree = subshell_parse(tree_operator);
	return (parse_tree);
}
