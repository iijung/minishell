/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:54:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 23:05:04 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

static void	loop_check_match(\
t_list *token, int *dquote_flag, int *parenthesis_dep)
{
	t_s_lex	*cur_token_data;

	while (token)
	{
		cur_token_data = token->content;
		if (cur_token_data->type == LEXEME_DQUOTE)
			*dquote_flag ^= 1;
		else if ((cur_token_data->type == LEXEME_PARENTHESIS_OPEN || \
				cur_token_data->type == LEXEME_PARENTHESIS_CLOSE) && \
				*dquote_flag == 0)
		{
			if (cur_token_data->type == LEXEME_PARENTHESIS_OPEN)
				(*parenthesis_dep)++;
			else
				(*parenthesis_dep)--;
		}
		token = token->next;
	}
}

static int	check_quote_parenthesis_match_error(t_list *token)
{
	int	dquote_flag;
	int	parenthesis_dep;

	dquote_flag = 0;
	parenthesis_dep = 0;
	loop_check_match(token, &dquote_flag, &parenthesis_dep);
	if (dquote_flag == 0 && parenthesis_dep == 0)
		return (0);
	else
		return (1);
}

void	clear_parse_tree(t_parse *root)
{
	t_parse	*left_tree;
	t_parse	*right_tree;

	left_tree = root->left;
	right_tree = root->right;
	if (left_tree)
	{
		clear_parse_tree(left_tree);
		free(left_tree);
	}
	if (right_tree)
	{
		clear_parse_tree(right_tree);
		free(right_tree);
	}
	ft_lstclear(&root->node, free);
}

void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	if (parse_tree->is_subshell)
		printf("this is SUBSHELL_NODE\n");
	ft_lstiter(parse_tree->node, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

t_parse	*parse(t_lex_lst *lexlst)
{
	t_parse	*root;

	if (check_quote_parenthesis_match_error(lexlst))
		return (NULL);
	root = split_with_operator(lexlst, ft_lstlast(lexlst));
	// debug_print_parse_tree(root);
	return (root);
}