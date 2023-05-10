/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:54:45 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 23:56:53 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

t_lex_lst	*get_type_operator(t_lex_lst *start, t_lex_lst *end, t_e_lex type)
{
	t_s_lex		*lex_data;
	int			dquote_flag;
	int			subshell_depth;

	dquote_flag = 0;
	subshell_depth = 0;
	while (start != end)
	{
		lex_data = start->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (subshell_depth == 0 && lex_data->type == type)
				return (start);
			else if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
				subshell_depth++;
			else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
				subshell_depth--;
		}
		start = start->next;
	}
	lex_data = end->content;
	if (dquote_flag == 0 && subshell_depth && lex_data->type == type)
		return (end);
	return (NULL);
}

t_lex_lst	*get_operator(t_lex_lst *start, t_lex_lst *end)
{
	t_lex_lst	*operator;

	operator = get_type_operator(start, end, LEXEME_AND);
	if (operator)
		return (operator);
	operator = get_type_operator(start, end, LEXEME_OR);
	if (operator)
		return (operator);
	return (NULL);
}

t_parse	*split_with_operator(t_lex_lst *start, t_lex_lst *end)
{
	t_lex_lst	*operator;
	t_lex_lst	*end_of_left_child;
	t_lex_lst	*rear;
	t_parse		*node;

	operator = get_operator(start, end);
	if (operator != NULL)
	{
		if (start->next == operator)
			end_of_left_child = start;
		else
		{
			rear = start;
			while (rear != operator)
			{
				end_of_left_child = rear;
				rear = rear->next;
			}
			if (operator== start || operator== end)
				return (NULL);
		}
		node = ft_calloc(1, sizeof(t_parse));
		node->left = split_with_operator(start, end_of_left_child);
		node->right = split_with_operator(operator->next, end);
		node->node = ft_lstnew(operator->content);
		return (node);
	}
	else
		return (make_new_node(start, end));
}
