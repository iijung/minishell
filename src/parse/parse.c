/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/04 10:45:21 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	ft_lstiter(parse_tree->token, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

t_list	*find_before_delemiter(t_list *tokens, enum e_lexeme token_type)
{
	t_list			*front;
	struct s_lexeme	*cur_token;

	cur_token = tokens->content;
	if (cur_token->type == token_type)
		return (NULL);
	front = tokens;
	tokens = tokens->next;
	while (tokens != NULL)
	{
		cur_token = tokens->content;
		if (cur_token->type == token_type)
			return (front);
		front = tokens;
		tokens = tokens->next;
	}
	return (NULL);
}

t_list	*find_end_of_left_node(t_list *tokens)
{
	t_list	*end_of_left_node;

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

int	check_quote_parenthesis_match_error(t_list *token)
{
	struct s_lexeme	*cur_token_data;
	int				dquote_flag;
	int				parenthesis_flag;

	dquote_flag = 0;
	parenthesis_flag = 0;
	cur_token_data = token->content;
	while (token)
	{
		cur_token_data = token->content;
		if (cur_token_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if ((cur_token_data->type == LEXEME_PARENTHESIS_OPEN || \
				cur_token_data->type == LEXEME_PARENTHESIS_CLOSE) && \
				dquote_flag == 0)
		{
			if (parenthesis_flag == 0 && cur_token_data->type == LEXEME_PARENTHESIS_OPEN)
				parenthesis_flag ^= 1;
			else if (parenthesis_flag == 1 && cur_token_data->type == LEXEME_PARENTHESIS_CLOSE)
				parenthesis_flag ^= 1;
			else
				return 1;
		}
		token = token->next;
	}
	if (dquote_flag == 0 && parenthesis_flag == 0)
		return (0);
	else
		return (1);
}

t_parse	*parse(t_list *tokens)
{
	t_parse			*root;
	t_list			*end_of_left_node;

	if (check_quote_parenthesis_match_error(tokens))
		return (NULL);
	root = ft_calloc(1, sizeof(t_parse));
	end_of_left_node = find_end_of_left_node(tokens);
	if (end_of_left_node != NULL)
	{
		root->token = end_of_left_node->next;
		root->right = parse(root->token->next);
		root->token->next = NULL;
		end_of_left_node->next = NULL;
		root->left = parse(tokens);
	}
	else
	{
		root->token = tokens;
		root->left = NULL;
		root->right = NULL;
	}
	return (root);
}
