/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:15:38 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 16:16:58 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	find_operator(\
t_lex_lst *lexlst, \
t_lex_lst **end_of_left_child, \
t_lex_lst **root_node, \
t_e_lex type)
{
	t_s_lex		*lex_data;	
	t_lex_lst	*prev_lex;
	int			dquote_flag;
	int			depth_parenthesis;

	dquote_flag = 0;
	depth_parenthesis = 0;
	lex_data = lexlst->content;
	if (lex_data->type == type)
	{
		*root_node = lexlst;
		end_of_left_child = NULL;
		return (1);
	}
	else if (lex_data->type == LEXEME_DQUOTE)
		dquote_flag ^= 1;
	else if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		depth_parenthesis++;
	else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		depth_parenthesis--;
	prev_lex = lexlst;
	lexlst = lexlst->next;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (depth_parenthesis == 0 && dquote_flag == 0
			&& lex_data->type == type)
		{
			*root_node = lexlst;
			*end_of_left_child = prev_lex;
			return (1);
		}
		else if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
			depth_parenthesis++;
		else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			depth_parenthesis--;
		prev_lex = lexlst;
		lexlst = lexlst->next;
	}
	return (0);
}

static int	find_root_node(\
	t_lex_lst *lexlst, t_lex_lst **end_of_left_child, t_lex_lst **root_node)
{
	if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_AND))
		return (1);
	else if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_OR))
		return (1);
	else if (find_operator(lexlst, end_of_left_child, root_node, LEXEME_PIPE))
		return (1);
	else
		return (0);
}

static void	*_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

static void	delete_ifs_token(t_lex_lst **root_node, t_lex_lst *read_root_node)
{
	t_lex_lst	*to_delete;

	to_delete = (*root_node)->next;
	if (to_delete != read_root_node)
		ft_lstdelone(to_delete, free);
}

t_parse	*operator_parse(t_lex_lst *lexlst)
{
	t_parse		*root;
	t_lex_lst	*end_of_left_child;
	t_lex_lst	*first_of_right_child;
	t_lex_lst	*root_node;

	root = ft_calloc(1, sizeof(t_parse));
	if (find_root_node(lexlst, &end_of_left_child, &root_node))
	{
		if (end_of_left_child == NULL || root_node->next == NULL)
			return (_free(root));
		end_of_left_child->next = NULL;
		root->left = parse(lexlst);
		if (root->left == NULL)
			return (_free(root));
		first_of_right_child = get_next_lextoken_nonifs(root_node->next);
		delete_ifs_token(&root_node, first_of_right_child);
		root->right = parse(first_of_right_child);
		if (root->right == NULL)
			return (_free(root));
		root_node->next = NULL;
		root->node = root_node;
		return (root);
	}
	root->node = lexlst;
	return (root);
}
