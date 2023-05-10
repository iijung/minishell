/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:54:45 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/10 23:45:19 by jaemjeon         ###   ########.fr       */
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

int	has_someting_before_parenthesis(t_lex_lst *lexlst)
{
	t_s_lex		*lex_data;

	lex_data = lexlst->content;
	if (lex_data->type == LEXEME_IFS)
		lexlst = lexlst->next;
	lex_data = lexlst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		return (0);
	return (1);
}

t_lex_lst	*get_someting_before_parenthesis(t_lex_lst **lexlst)
{
	t_lex_lst	*start_lexlst;
	t_lex_lst	*end_of_someting;
	t_s_lex		*lex_data;

	start_lexlst = *lexlst;
	while (1)
	{
		lex_data = (*lexlst)->next->content;
		if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		{
			end_of_someting = *lexlst;
			break ;
		}
		(*lexlst) = (*lexlst)->next;
	}
	(*lexlst) = (*lexlst)->next;
	end_of_someting->next = NULL;
	return (start_lexlst);
}

t_lex_lst	*find_first_parenthesis_open(t_lex_lst *lexlst)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (lexlst);
	}
	return (NULL);
}

t_lex_lst	*find_before_last_parenthesis_close(t_lex_lst *lexlst)
{
	t_lex_lst	*last_before_last;
	t_s_lex		*lex_data;
	int			dquote_flag;

	dquote_flag = 0;
	last_before_last = lexlst;
	lex_data = last_before_last->next->content;
	if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
		return (last_before_last);
	lexlst = lexlst->next;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			last_before_last = lexlst;
		lexlst = lexlst->next;
	}
	return (last_before_last);
}

void	clear_parenthesis(t_lex_lst **lexlst)
{
	t_lex_lst	*cur_lexlst;
	t_lex_lst	*close_parenthesis;

	cur_lexlst = *lexlst;
	*lexlst = cur_lexlst->next;
	ft_lstdelone(cur_lexlst, free);
	cur_lexlst = find_before_last_parenthesis_close(*lexlst);
	close_parenthesis = cur_lexlst->next;
	ft_lstdelone(close_parenthesis, free);
	cur_lexlst->next = NULL;
}

t_parse	*get_someting_after_parenthesis(t_lex_lst **lexlst)
{
	t_parse		*node;
	t_lex_lst	*last_parenthesis_close;
	t_lex_lst	*someting;

	node = ft_calloc(1, sizeof(t_parse));
	last_parenthesis_close = find_before_last_parenthesis_close(*lexlst);
	someting = last_parenthesis_close->next->next;
	last_parenthesis_close->next->next = NULL;
	node->node = someting;
	return (node);
}

int	has_subshell(t_lex_lst *lexlst)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	while (lexlst)
	{
		lex_data = lexlst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
			return (1);
		lexlst = lexlst->next;
	}
	return (0);
}

t_parse	*expand_subshell(t_parse *root)
{
	t_parse	*new_root;

	if (!has_subshell(root->node))
		return (root);
	new_root = ft_calloc(1, sizeof(t_parse));
	if (has_someting_before_parenthesis(root->node))
		new_root->node = get_someting_before_parenthesis(&(root->node));
	new_root->is_subshell = 1;
	new_root->right = get_someting_after_parenthesis(&(root->node));
	clear_parenthesis(&(root->node));
	new_root->left = parse(root->node);
	return (new_root);
}
