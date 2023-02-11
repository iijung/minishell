/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:13:05 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/12 01:07:43 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "util.h"

// token -> word, pipe, &&, ||

void	init_stack(t_stack *stack, int capacity)
{
	stack->cursor = -1;
	stack->capacity = capacity;
	stack->arr_data = ft_calloc(capacity, sizeof(t_list));
	ft_assert(stack->arr_data, __FILE__, __LINE__);
}

void	init_parse_tree(t_parse_tree *root)
{
	ft_memset(root, 0, sizeof(t_parse_tree));
	ft_memset(&root->node, 0, sizeof(t_parse_node));

}

int	lr_parse(t_parse_tree **cur_parsing_node, t_parse_node *token)
{

}

t_parse_tree	*parse(t_list *lst_token)
{
	t_stack			stack;
	t_parse_tree	root_parse_tree;
	t_parse_tree	*cur_tree_node;
	int				parse_state;
	int				(*lr_parse[26])(t_parse_tree **cur_tree_node, t_parse_node token);

	init_stack(&stack, ft_lstsize(lst_token));
	init_parse_tree(&root_parse_tree);
	parse_state = 0;
	cur_tree_node = &root_parse_tree;
	while (lst_token)
	{
		parse_state = lr_parse(&cur_tree_node, lst_token->content);
		lst_token = lst_token->next;
	}
	ft_lstclear(&lst_token, NULL);
}