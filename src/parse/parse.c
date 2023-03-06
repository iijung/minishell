/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:20:34 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 01:33:04 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

// string ifs dquote | string || ifs string ....으로 들어옴

void	init_lr_stack(t_lr_stack *stack, size_t capacity)
{
	stack->stk_capacity = capacity;
	stack->stk_state = malloc(stack->stk_capacity * sizeof(int));
	stack->stk_token = malloc(stack->stk_capacity * sizeof(t_lex_token *));
	stack->idx_state = -1;
	stack->idx_token = -1;
	stk_state_push(stack, 0);
}

void	destroy_lr_stack(t_lr_stack *stack)
{
	free(stack->stk_state);
	free(stack->stk_token);
}

t_parse_tree	*parse(t_lex_token *lst_token)
{
	t_parse_tree	*root;
	t_lr_stack		lr_stack;
	static int	(*const lr_func[23])(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token) = \
	{
		lr_state_0, lr_state_1, lr_state_2, lr_state_3, lr_state_4, lr_state_5, \
		lr_state_6, lr_state_7, lr_state_8, lr_state_9, lr_state_10, lr_state_11, \
		lr_state_12, lr_state_13, lr_state_14, lr_state_15, lr_state_16, lr_state_17, \
		lr_state_18, lr_state_19, lr_state_20, lr_state_21, lr_state_22
	};

	root = NULL;
	init_lr_stack(&lr_stack, ft_lstsize(lst_token));
	while (lr_stack.stk_state[lr_stack.idx_state] != -1)
	{
		while (lst_token->type == E_IFS)
			lst_token = lst_token->next;
		if (lr_func[lr_stack.stk_state[lr_stack.idx_state]]\
				(&root, &lr_stack, lst_token))
			lst_token = lst_token->next;
	}
	destroy_lr_stack(&lr_stack);
	return (root);
}
