#include "parse.h"

void	f(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static char const * const	token_string_value[] = \
	{
		[E_AND] = "&&",
		[E_OR] = "||",
		[E_SUB_S] = "(",
		[E_SUB_E] = ")",
		[E_PIPE] = "|",
		[E_READ] = "<",
		[E_HEREDOC] = "<<",
		[E_WRITE] = ">",
		[E_APPEND] = ">>",
		[E_END] = "newline"
	};
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(token_string_value[token->type], 2);
	clear_parse_tree(parse_tree);
}

void	s(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	parse_tree = NULL;
	stk_token_push(stack, token);
}

t_parse_tree	*new_internal_node(void *child3, void *child2, void *child1, unsigned int type)
{
	t_parse_tree	*new_node;

	new_node = ft_calloc(1, sizeof(t_parse_tree));
	new_node->child[0] = child1;
	new_node->child[1] = child2;
	new_node->child[2] = child3;
	new_node->type = type;
}

void	acc(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	*parse_tree = new_internal_node(stk_token_pop(stack), NULL, NULL, E_S);
}

void	r1(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_APL));
}

void	r2(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_APL));
}

void	r3(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_OPL));
}

void	r4(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_OPL));
}

void	r5(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_WL));
}

void	r6(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(stk_token_pop(stack), stk_token_pop(stack), stk_token_pop(stack), E_PL));
}

void	r7(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_WL));
}

void	r8(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, stk_token_pop(stack), stk_token_pop(stack), E_WL));
}

void	r9(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_WL));
}

void	r10(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_W));
}

void	r11(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, stk_token_pop(stack), stk_token_pop(stack), E_W));
}

void	r12(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_W));
}

void	r13(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
}

void	r14(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
}

void	r15(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	stk_token_push(stack, new_internal_node(NULL, NULL, stk_token_pop(stack), E_REDIRECT));
}

void	acc(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{

}

int	lr_state_0(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, 1, 2, 4, 3, 6, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int	lr_state_1(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{s, f, f, f, f, f, f, f, f, f, acc};
	static int next_status[11] = {13, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int	lr_state_2(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r, s, f, r, f, f, f, f, f, f, r};
	static int next_status[11] = {2, 14, -1, 2, -1, -1, -1, -1, -1, -1, 2};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int	lr_state_3(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) =
			{r, r, f, r, s, f, f, f, f, f, r};
	static int next_status[11] = {4, 4, -1, 4, 15, -1, -1, -1, -1, -1, 4};
	static int goto_table[7] = {-1,-1,-1,-1,-1,-1,-1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_4(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, s, s, s, s, s, r};
	static int next_status[11] = {7, 7, -1, 7, 7, 7, 9, 10, 11, 12, 7};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_5(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12};
	static int goto_table[7] = {-1, 17, 2, 4, 3, 6, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_6(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {9, 9, -1, 9, 9, 9, 9, 9, 9, 9, 9};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_7(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {10, 10, -1, 10, 10, 10, 10, 10, 10, 10, 10};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
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
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_9(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_10(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_11(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_12(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
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
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
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
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_15(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, -1, 21, -1, 6, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_16(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {8, 8, -1, 8, 8, 8, 8, 8, 8, 8, 8};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
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
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_18(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {11, 11, -1, 11, 11, 11, 11, 11, 11, 11};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_19(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, s, f, r, f, f, f, f, f, f, r};
	static int next_status[11] = {1, 14, -1, 1, -1, -1, -1, -1, -1, -1, 1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_20(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, s, f, f, f, f, f, r};
	static int next_status[11] = {3, 3, -1, 3, 15, -1, -1, -1, -1, -1, 3};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int lr_state_21(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, s, s, s, s, s, r};
	static int next_status[11] = {6, 6, -1, 6, 6, 7, 9, 10, 11, 12, 6};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}

int	lr_state_22(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static void (*const action[11])\
		(t_parse_tree **tree, t_lr_stack *stack, t_lex_token *token) = 
			{r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {5, 5, -1, 5, 5, 5, 5, 5, 5, 5, 5};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};

	if (stack->idx_state == stack->idx_token)
	{
		if (goto_table[token->type] == -1)
			f(parse_tree, stack, token);
		stk_state_push(stack, goto_table[token->type]);
	}
	else
	{
		action[token->type](parse_tree, stack, token);
		stk_state_push(stack, next_status[token->type]);
	}
}
