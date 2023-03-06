#include "parse.h"

void	r6(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_PL));
	stk_state_pop(stack);
	stk_state_pop(stack);
	stk_state_pop(stack);
}

void	r7(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_PL));
	stk_state_pop(stack);
}

void	r8(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, stk_token_pop(stack), stk_token_pop(stack), E_WL));
	stk_state_pop(stack);
	stk_state_pop(stack);
}

void	r9(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_WL));
	stk_state_pop(stack);
}

void	r10(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	parse_tree = NULL;
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_W));
	stk_state_pop(stack);
}