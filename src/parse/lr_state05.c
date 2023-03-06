#include "parse.h"

int lr_state_20(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r3, r3, f, r3, s, f, f, f, f, f, r3};
	static int next_status[11] = {3, 3, -1, 3, 15, -1, -1, -1, -1, -1, 3};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[get_nonterminal_type(stack)] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[get_nonterminal_type(stack)]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		if (action[token->type] == s || action[token->type] == f)
		{
			stk_state_push(stack, next_status[token->type]);
			return (1);
		}
	}
	return (0);
}

int lr_state_21(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r6, r6, f, r6, r6, s, s, s, s, s, r6};
	static int next_status[11] = {6, 6, -1, 6, 6, 7, 9, 10, 11, 12, 6};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[get_nonterminal_type(stack)] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[get_nonterminal_type(stack)]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		if (action[token->type] == s || action[token->type] == f)
		{
			stk_state_push(stack, next_status[token->type]);
			return (1);
		}
	}
	return (0);
}

int	lr_state_22(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r5, r5, f, r5, r5, r5, r5, r5, r5, r5, r5};
	static int next_status[11] = {5, 5, -1, 5, 5, 5, 5, 5, 5, 5, 5};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[get_nonterminal_type(stack)] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[get_nonterminal_type(stack)]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		if (action[token->type] == s || action[token->type] == f)
		{
			stk_state_push(stack, next_status[token->type]);
			return (1);
		}
	}
	return (0);
}