#ifndef PARSE_H
# define PARSE_H
# include "lexer.h"

typedef struct s_parse_tree
{
	t_lex_token			*content;
	struct s_parse_tree	*parent;
	struct s_parse_tree	*child[3];
}	t_parse_tree;

typedef struct s_lr_stack
{
	t_lex_token	**stk_token;
	int			idx_token;
	int			*stk_state;
	int			idx_state;
	int			stk_capacity;
}	t_lr_stack;

t_parse_tree	*parse(t_lex_token *lst_token);

int	lr_state_0(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_1(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_2(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_3(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_4(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_5(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_6(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_7(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_8(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_9(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_10(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_11(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_12(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_13(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_14(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_15(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_16(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_17(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_18(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_19(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_20(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_21(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);
int	lr_state_22(t_parse_tree **parse_tree, t_lr_stack *stack, t_lex_token *token);

int		stk_token_push(t_lr_stack *stack, t_token *token);
t_token	*stk_token_pop(t_lr_stack *stack);
void	stk_state_push(t_lr_stack *stack, int state);
int		stk_state_pop(t_lr_stack *stack);

#endif