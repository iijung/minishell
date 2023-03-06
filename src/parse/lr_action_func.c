#include "parse.h"

void	f(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static char * const	token_string_value[] = \
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
	// clear_parse_tree(parse_tree);
}

void	s(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	parse_tree = NULL;
	stk_token_push(stack, token);
}

void	acc(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	*parse_tree = new_internal_node(NULL, NULL, stk_token_pop(stack), E_S);
	stk_state_pop(stack);
}
