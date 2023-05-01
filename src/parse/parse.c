/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:29:46 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/01 17:07:48 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

// t_parse	*make_parse_node(t_list *tokens)
// {
	
// }

// void	make_subshell_nodes(t_list *tokens)
// {

// }

t_list	*find_before_delemiter(t_list *tokens, enum e_lexeme token_type)
{
	t_list			*rear;
	struct s_lexeme	*cur_token;

	cur_token = tokens->content;
	if (cur_token->type == token_type)
		return (NULL);
	rear = tokens;
	tokens = tokens->next;
	while (tokens != NULL)
	{
		cur_token = tokens->content;
		if (cur_token->type == token_type)
			return (rear);
		rear = tokens;
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

t_parse *parse(t_list *tokens)
{
	t_parse	*root;
	t_list	*end_of_left_node;

	root = malloc(sizeof(t_parse));
	// make_subshell_nodes(tokens);
	end_of_left_node = find_end_of_left_node(tokens);
	if (end_of_left_node != NULL)
	{
		root->token = end_of_left_node->next;
		// root->left = tokens;
		// root->right = root->token->next;
		root->right = parse(root->token->next);
		end_of_left_node->next = NULL;
		root->left = parse(tokens);
		root->token->next = NULL;
	}
	else
	{
		root->token = tokens;
		root->left = NULL;
		root->right = NULL;
	}
	return (root);
}