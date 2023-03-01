#include "lexer.h"
#include "parse.h"

// string ifs dquote | string || ifs string ....으로 들어옴

void	init_lr_stack(t_lr_stack *stack)
{
	stack->stk_capacity = ft_lstsize(stack);
	stack->stk_state = malloc(stack->stk_capacity * sizeof(int));
	stack->stk_token = malloc(stack->stk_capacity * sizeof(t_lex_token *));
	stack->idx_state = -1;
	stack->idx_token = -1;
}

t_parse_tree	*parse(t_lex_token *lst_token)
{
	t_parse_tree	*root;
	int				lr_state;
	t_lr_stack		lr_stack;
	static int	(*const lr_func[22])(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token) = \
	{
		lr_state_0, lr_state_1, lr_state_2, lr_state_3, lr_state_4, lr_state_5, \
		lr_state_6, lr_state_7, lr_state_8, lr_state_9, lr_state_10, lr_state_11, \
		lr_state_12, lr_state_13, lr_state_14, lr_state_15, lr_state_16, lr_state_17, \
		lr_state_18, lr_state_19, lr_state_20, lr_state_21, lr_state_22
	};

	root = NULL;
	init_lr_stack(&lr_stack);
	lr_state = 0;
	while (lr_state != -1)
	{
		lr_state = lr_func[lr_state](&root, &lr_stack, lst_token);
		lst_token = lst_token->next;
	}
}