/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_reduce03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 04:27:16 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 04:36:37 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	r11(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, stk_token_pop(stack), stk_token_pop(stack), E_W));
	stk_state_pop(stack);
	stk_state_pop(stack);
}

void	r12(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
	stk_state_pop(stack);
}

void	r13(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
	stk_state_pop(stack);
}

void	r14(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
	stk_state_pop(stack);
}

void	r15(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
	stk_state_pop(stack);
}