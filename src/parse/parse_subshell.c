/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:55:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/11 03:53:25 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"

int	has_something_before_parenthesis(t_lex_lst *lexlst)
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

t_lex_lst	*get_something_before_parenthesis(t_lex_lst **lexlst)
{
	t_lex_lst	*start_lexlst;
	t_lex_lst	*end_of_something;
	t_s_lex		*lex_data;

	start_lexlst = *lexlst;
	while (1)
	{
		lex_data = (*lexlst)->next->content;
		if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
		{
			end_of_something = *lexlst;
			break ;
		}
		(*lexlst) = (*lexlst)->next;
	}
	(*lexlst) = (*lexlst)->next;
	return (make_new_lexlst(*lexlst, end_of_something));
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
	t_lex_lst	*prev_lexlst;
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
			last_before_last = prev_lexlst;
		prev_lexlst = lexlst;
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

t_parse	*get_something_after_parenthesis(t_lex_lst **lexlst)
{
	t_parse		*node;
	t_lex_lst	*last_parenthesis_close;
	t_lex_lst	*something;

	node = ft_calloc(1, sizeof(t_parse));
	last_parenthesis_close = find_before_last_parenthesis_close(*lexlst);
	something = last_parenthesis_close->next->next;
	node->node = make_new_lexlst(something, ft_lstlast(something));
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

int	has_something_after_parenthesis(t_lex_lst *lexlst)
{
	t_lex_lst	*after_parenthesis;
	t_s_lex		*lex_data;	

	after_parenthesis = (find_before_last_parenthesis_close(lexlst))->next->next;
	if (after_parenthesis == NULL)
		return (0);
	lex_data = after_parenthesis->content;
	if (lex_data->type == LEXEME_IFS && after_parenthesis->next == NULL)
		return (0);
	else
		return (1);
}

t_parse	*expand_subshell(t_parse *root)
{
	t_parse	*new_root;

	if (!has_subshell(root->node))
		return (root);
	new_root = ft_calloc(1, sizeof(t_parse));
	new_root->is_subshell = 1;
	if (has_something_before_parenthesis(root->node))
		new_root->node = get_something_before_parenthesis(&(root->node));
	if (has_something_after_parenthesis(root->node))
		new_root->right = get_something_after_parenthesis(&(root->node));
	clear_parenthesis(&(root->node));
	new_root->left = parse(root->node);
	clear_parse_tree(root, NULL);
	free(root);
	return (new_root);
}