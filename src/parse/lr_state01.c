#include "parse.h"

void	f(t_parse_tree **parse_tree)
{
	
}

void	s(t_parse_tree **parse_tree)
{

}

void	r(t_parse_tree **parse_tree)
{

}

int	lr_state_0(t_parse_tree **parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree *tree) = \
		{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {0, 0, 5, 0, 0, 7, 9, 10, 11, 12, 0};
	static int goto_table[7] = {0, 1, 2, 4, 3, 6, 8};
}

int	lr_state_1(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree *tree) = \
		{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {0, 0, 5, 0, 0, 7, 9, 10, 11, 12, 0};
	static int goto_table[7] = {0, 1, 2, 4, 3, 6, 8};
	
}

int	lr_state_2(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree * tree) = \
		{r, s, f, r, f, f, f, f, f, f, r};
	static int next_status[11] = {2, 14, 0, 2, 0, 0, 0, 0, 0, 0, 2};
	static int goto_table[7] = {0, 0, 0, 0, 0, 0, 0};
}

int	lr_state_3(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree * tree) =
		{r, r, f, r, s, f, f, f, f, f, r};
	static int next_status[11] = {4, 4, 0, 4, 15, 0, 0, 0, 0, 0, 4};
	static int goto_table[7] = {0, 0, 0, 0, 0, 0, 0};
}

int	lr_state_4(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_5(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_6(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_7(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};

}

int	lr_state_8(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_9(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_10(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_11(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_12(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_13(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_14(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_15(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_16(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_17(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_18(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_19(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_20(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_21(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}

int	lr_state_22(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {};
	static int next_status[11] = {};
	static int goto_table[7] = {};
	
}
