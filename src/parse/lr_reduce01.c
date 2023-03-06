#include "parse.h"

void	r1(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_APL));
	stk_state_pop(stack);
	stk_state_pop(stack);
	stk_state_pop(stack);
}

void	r2(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_APL));
	stk_state_pop(stack);
}

void	r3(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_OPL));
	stk_state_pop(stack);
	stk_state_pop(stack);
	stk_state_pop(stack);
}

void	r4(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_OPL));
	stk_state_pop(stack);
}

void	r5(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_WL));
	stk_state_pop(stack);
	stk_state_pop(stack);
	stk_state_pop(stack);
}