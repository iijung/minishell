/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/05 16:05:10 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	ft_lstiter(parse_tree->node, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

t_lex	*find_before_delemiter(t_lex *tokens, enum e_lexeme token_type)
{
	int				dquote_flag;
	t_lex			*front;
	struct s_lexeme	*cur_token;

	dquote_flag = 0;
	cur_token = tokens->content;
	if (cur_token->type == token_type)
		return (NULL);
	front = tokens;
	tokens = tokens->next;
	while (tokens != NULL)
	{
		cur_token = tokens->content;
		if (cur_token->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		if (dquote_flag == 0 && cur_token->type == token_type)
			return (front);
		front = tokens;
		tokens = tokens->next;
	}
	return (NULL);
}

t_lex	*find_prev2split(t_lex *tokens)
{
	t_lex	*end_of_left_node;

	end_of_left_node = find_before_delemiter(tokens, LEXEME_AND);
	if (end_of_left_node != NULL)
		return (end_of_left_node);
	end_of_left_node = find_before_delemiter(tokens, LEXEME_OR);
	if (end_of_left_node != NULL)
		return (end_of_left_node);
	end_of_left_node = find_before_delemiter(tokens, LEXEME_PIPE);
	if (end_of_left_node != NULL)
		return (end_of_left_node);
	return (NULL);
}

static int	loop_tokens(\
		struct s_lexeme *token, int *dquote_flag, int *parenthesis_flag)
{
	if (token->type == LEXEME_DQUOTE)
		*dquote_flag ^= 1;
	else if (*dquote_flag == 0
		&& (token->type == LEXEME_PARENTHESIS_OPEN
			|| token->type == LEXEME_PARENTHESIS_CLOSE))
	{
		if (*parenthesis_flag == 0
			&& token->type == LEXEME_PARENTHESIS_OPEN)
			*parenthesis_flag ^= 1;
		else if (*parenthesis_flag == 1
			&& token->type == LEXEME_PARENTHESIS_CLOSE)
			*parenthesis_flag ^= 1;
		else
			return (1);
	}
	return (0);
}

static int	check_dquote_parenthesis_match_error(t_lex *tokens)
{
	struct s_lexeme	*cur_token_data;
	int				dquote_flag;
	int				parenthesis_flag;

	dquote_flag = 0;
	parenthesis_flag = 0;
	while (tokens)
	{
		cur_token_data = tokens->content;
		if (loop_tokens(cur_token_data, &dquote_flag, &parenthesis_flag))
			return (1);
		tokens = tokens->next;
	}
	if (dquote_flag == 0 && parenthesis_flag == 0)
		return (0);
	else
		return (1);
}

t_lex	*get_last_parenthesis_close(t_lex *tokens)
{
	t_lex			*last_close;
	struct s_lexeme	*cur_lex;
	int				dquote_flag;

	dquote_flag = 0;
	while (tokens)
	{
		cur_lex = tokens->content;
		if (cur_lex->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && cur_lex->type == LEXEME_PARENTHESIS_CLOSE)
			last_close = tokens;
		tokens = tokens->next;
	}
	return (last_close);
}

t_parse	*parse_subshell(t_lex *tokens)
{
	t_lex	*open;
	t_parse	*subshell_root;

	open = tokens;
	subshell_root = ft_calloc(1, sizeof(t_parse));
	subshell_root->is_subshell = 1;
	tokens = tokens->next;
	ft_lstdelone(open, free);
	ft_lstdelone(get_last_parenthesis_close(tokens), free);
	subshell_root->left = parse(tokens);
	return (subshell_root);
}


t_parse	*parse(t_lex *tokens)
{
	t_parse			*root;
	t_lex			*prev_token;
	struct s_lexeme	*lexeme_token;

	if (check_dquote_parenthesis_match_error(tokens))
		return (NULL);
	root = ft_calloc(1, sizeof(t_parse));
	root->is_subshell = 0;
	prev_token = find_prev2split(tokens);
	if (prev_token == NULL)
	{
		lexeme_token = tokens->content;
		if (lexeme_token->type == LEXEME_PARENTHESIS_OPEN)
		{
			root->is_subshell = 1;
			root->left = parse_subshell(tokens);
		}
		root->node = tokens;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		lexeme_token = prev_token->next->content;
		if (lexeme_token->type == LEXEME_PARENTHESIS_OPEN)
			root->left = parse_subshell(prev_token->next);
		else
		{
			root->node = prev_token->next;
			root->right = parse(root->node->next);
			root->node->next = NULL;
			prev_token->next = NULL;
			root->left = parse(tokens);
		}
	}
	return (root);
}
