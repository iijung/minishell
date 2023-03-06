#include "parse.h"

void	f(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	static char * const	token_string_value[] = \
	{
		[LEXEME_AND] = "&&",
		[LEXEME_OR] = "||",
		[LEXEME_SUB_S] = "(",
		[LEXEME_SUB_E] = ")",
		[LEXEME_PIPE] = "|",
		[LEXEME_READ] = "<",
		[LEXEME_HEREDOC] = "<<",
		[LEXEME_WRITE] = ">",
		[LEXEME_APPEND] = ">>",
		[LEXEME_END] = "newline"
	};

	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(token_string_value[token->type], 2);
	clear_lr_stack(stack);
	// clear_parse_tree(*parse_tree);
	*parse_tree = NULL;
}

void	s(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	parse_tree = NULL;
	stk_token_push(stack, token);
}

void	acc(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token)
{
	token = NULL;
	*parse_tree = new_internal_node(NULL, NULL, stk_token_pop(stack), E_S);
	stk_state_pop(stack);
}
