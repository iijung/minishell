#include "parse.h"

void	f(t_parse_tree **parse_tree)
{
	clear_parse_tree(parse_tree);
	// 
}

void	s(t_parse_tree **parse_tree)
{

}

void	r(t_parse_tree **parse_tree)
{

}

int	lr_state_0(t_parse_tree **parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree **tree, t_lex_token *token) = \
		{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, 1, 2, 4, 3, 6, 8};

	
}

int	lr_state_1(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree *tree, t_lex_token *token) = \
		{f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, 1, 2, 4, 3, 6, 8};
	
}

int	lr_state_2(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree *tree, t_lex_token *token) = \
		{r, s, f, r, f, f, f, f, f, f, r};
	static int next_status[11] = {2, 14, -1, 2, -1, -1, -1, -1, -1, -1, 2};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int	lr_state_3(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree *tree, t_lex_token *token) =
		{r, r, f, r, s, f, f, f, f, f, r};
	static int next_status[11] = {4, 4, -1, 4, 15, -1, -1, -1, -1, -1, 4};
	static int goto_table[7] = {-1,-1,-1,-1,-1,-1,-1};
}

int lr_state_4(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, s, s, s, s, s, r};
	static int next_status[11] = {7, 7, -1, 7, 7, 7, 9, 10, 11, 12, 7};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};
}

int lr_state_5(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12};
	static int goto_table[7] = {-1, 17, 2, 4, 3, 6, 8};
}

int lr_state_6(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {9, 9, -1, 9, 9, 9, 9, 9, 9, 9, 9};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_7(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {10, 10, -1, 10, 10, 10, 10, 10, 10, 10, 10};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_8(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, f, f, f, s, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_9(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_10(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_11(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_12(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, f, f, f, r, f, f, f, f, f};
	static int next_status[11] = {-1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_13(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, 19, 4, 3, 6, 8};
}

int lr_state_14(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, -1, 4, 20, 6, 8};
}

int lr_state_15(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {f, f, s, f, f, s, s, s, s, s, f};
	static int next_status[11] = {-1, -1, 5, -1, -1, 7, 9, 10, 11, 12, -1};
	static int goto_table[7] = {-1, -1, -1, 21, -1, 6, 8};
}

int lr_state_16(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {8, 8, -1, 8, 8, 8, 8, 8, 8, 8, 8};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_17(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {s, f, f, s, f, f, f, f, f, f, f};
	static int next_status[11] = {13, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_18(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {11, 11, -1, 11, 11, 11, 11, 11, 11, 11};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_19(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, s, f, r, f, f, f, f, f, f, r};
	static int next_status[11] = {1, 14, -1, 1, -1, -1, -1, -1, -1, -1, 1};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_20(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, s, f, f, f, f, f, r};
	static int next_status[11] = {3, 3, -1, 3, 15, -1, -1, -1, -1, -1, 3};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}

int lr_state_21(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, s, s, s, s, s, r};
	static int next_status[11] = {6, 6, -1, 6, 6, 7, 9, 10, 11, 12, 6};
	static int goto_table[7] = {-1, -1, -1, -1, -1, 16, 8};
}

int	lr_state_22(t_parse_tree *parse_tree, t_lex_token *token)
{
	static void (*const action[11])(t_parse_tree) = {r, r, f, r, r, r, r, r, r, r, r};
	static int next_status[11] = {5, 5, -1, 5, 5, 5, 5, 5, 5, 5, 5};
	static int goto_table[7] = {-1, -1, -1, -1, -1, -1, -1};
}
