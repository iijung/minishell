#include "parse.h"

int	stk_token_push(t_lr_stack *stack, void *node)
{
	if (stack->idx_token == stack->stk_capacity)
		return (1);
	stack->idx_token++;
	stack->stk_token[stack->idx_token] = node;
	return (0);
}

void	*stk_token_pop(t_lr_stack *stack)
{
	if (stack->idx_token == -1)
		return (NULL);
	stack->idx_token--;
	return (stack->stk_token[stack->idx_token + 1]);
}

int	stk_state_push(t_lr_stack *stack, int state)
{
	if (stack->idx_state == stack->stk_capacity)
		return (1);
	stack->idx_state++;
	stack->stk_state[stack->idx_state] = state;
	return (0);
}

int	stk_state_pop(t_lr_stack *stack)
{
	if (stack->idx_state == -1)
		return (-1);
	stack->idx_state--;
	return (stack->stk_state[stack->idx_state + 1]);
}

t_parse_tree	*new_internal_node(void *child3, void *child2, void *child1, unsigned int type)
{
	t_parse_tree	*new_node;

	new_node = ft_calloc(1, sizeof(t_parse_tree));
	new_node->child[0] = child1;
	new_node->child[1] = child2;
	new_node->child[2] = child3;
	new_node->type = type;
	return (new_node);
}
