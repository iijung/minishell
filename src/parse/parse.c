#include "parse.h"
#include "lexer.h"

// string ifs dquote | string || ifs string ....으로 들어옴


t_parse_tree	*parse(t_lex_token *lst_token)
{
	t_parse_tree	*root;
	int				lr_state;
	static int	(*const lr_func[22])(t_parse_tree **parse_tree, t_lex_token *token) = \
	{
		lr_state_0, lr_state_1, lr_state_2, lr_state_3, lr_state_4, lr_state_5, \
		lr_state_6, lr_state_7, lr_state_8, lr_state_9, lr_state_10, lr_state_11, \
		lr_state_12, lr_state_13, lr_state_14, lr_state_15, lr_state_16, lr_state_17, \
		lr_state_18, lr_state_19, lr_state_20, lr_state_21, lr_state_22
	};

	root = NULL;
	lr_state = 0;
	while (lr_state != -1)
	{
		lr_state = lr_func[lr_state](&root, lst_token);
		lst_token = lst_token->next;
	}
}