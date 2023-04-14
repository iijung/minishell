#include "parse.h"

int lr_state_15(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, -1, 21, -1, 6, 8};

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

int lr_state_16(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r8, r8, f, r8, r8, r8, r8, r8, r8, r8, r8};
	static int next_status[11] = {8, 8, -1, 8, 8, 8, 8, 8, 8, 8, 8};
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

int lr_state_17(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{s, f, f, s, f, f, f, f, f, f, f};
	static int next_status[11] = {13, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1};
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

int lr_state_18(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r11, r11, f, r11, r11, r11, r11, r11, r11, r11, r11};
	static int next_status[11] = {11, 11, -1, 11, 11, 11, 11, 11, 11, 11};
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

int lr_state_19(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r1, s, f, r1, f, f, f, f, f, f, r1};
	static int next_status[11] = {1, 14, -1, 1, -1, -1, -1, -1, -1, -1, 1};
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