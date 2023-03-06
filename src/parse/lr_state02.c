#include "parse.h"

int lr_state_5(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, 17, 2, 4, 3, 6, 8};

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

int lr_state_6(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r9, r9, f, r9, r9, r9, r9, r9, r9, r9, r9};
	static int next_status[11] = {9, 9, -1, 9, 9, 9, 9, 9, 9, 9, 9};
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

int lr_state_7(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r10, r10, f, r10, r10, r10, r10, r10, r10, r10, r10};
	static int next_status[11] = {10, 10, -1, 10, 10, 10, 10, 10, 10, 10, 10};
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

int lr_state_8(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, f, f, f, s, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1};
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

int lr_state_9(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, f, f, f, r12, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1};
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