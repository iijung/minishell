#include "parse.h"

int lr_state_10(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, f, f, f, r13, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[stack->stk_token[stack->idx_token]->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[stack->stk_token[stack->idx_token]->type]);
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

int lr_state_11(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, f, f, f, r14, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[stack->stk_token[stack->idx_token]->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[stack->stk_token[stack->idx_token]->type]);
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

int lr_state_12(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, f, f, f, r15, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[stack->stk_token[stack->idx_token]->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[stack->stk_token[stack->idx_token]->type]);
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

int lr_state_13(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, 19, 4, 3, 6, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[stack->stk_token[stack->idx_token]->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[stack->stk_token[stack->idx_token]->type]);
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

int lr_state_14(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, -1, 4, 20, 6, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[stack->stk_token[stack->idx_token]->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[stack->stk_token[stack->idx_token]->type]);
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