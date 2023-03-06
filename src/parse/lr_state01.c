#include "parse.h"

int	lr_state_0(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, 1, 2, 4, 3, 6, 8};

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

int	lr_state_1(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{s, f, f, f, f, f, f, f, f, f, acc};
	static int next_status[11] = {13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
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
		if (action[token->type] == s || action[token->type] == f || action[token->type] == acc)
		{
			stk_state_push(stack, next_status[token->type]);
			return (1);
		}
	}
	return (0);
}

int	lr_state_2(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r2, s, f, r2, f, f, f, f, f, f, r2};
	static int next_status[11] = {2, 14, -1, 2, -1, -1, -1, -1, -1, -1, 2};
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

int	lr_state_3(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r4, r4, f, r4, s, f, f, f, f, f, r4};
	static int next_status[11] = {4, 4, -1, 4, 15, -1, -1, -1, -1, -1, 4};
	static int goto_table[7] = {-1,-1,-1,-1,-1,-1,-1};

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

int lr_state_4(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r7, r7, f, r7, r7, s, s, s, s, s, r7};
	static int next_status[11] = {7, 7, -1, 7, 7, 7, 9, 10, 11, 12, 7};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};

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