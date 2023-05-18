/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:54:48 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/19 01:58:03 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parse.h"
#include "parse_inner_util.h"

t_lex_lst	*get_root_node(t_lex_lst **token_lst)
{
	t_lex_lst	*root_node;

	root_node = get_type_node(*token_lst, LEXEME_AND);
	if (root_node)
		return (root_node);
	root_node = get_type_node(*token_lst, LEXEME_OR);
	if (root_node)
		return (root_node);
	root_node = get_type_node(*token_lst, LEXEME_PIPE);
	if (root_node)
		return (root_node);
	return (NULL);
}

void	split_by_subshell(
	t_lex_lst *token_lst,
	t_parse **left,
	t_parse **right,
	t_lex_lst **mid
)
{
	t_lex_lst	*before_first_subshell_open;
	t_lex_lst	*first_subshell_open;
	t_lex_lst	*before_last_subshell_close;
	t_lex_lst	*tmp_token1;
	t_lex_lst	*tmp_token2;

	before_first_subshell_open = \
			get_before_first_subshell_open(token_lst, &first_subshell_open);
	before_last_subshell_close = get_before_last_subshell_close(token_lst);
	if (before_first_subshell_open)
		before_first_subshell_open->next = NULL;
	tmp_token1 = first_subshell_open->next;
	ft_lstdelone(first_subshell_open, free);
	tmp_token2 = before_last_subshell_close->next;
	before_last_subshell_close->next = NULL;
	*left = parse(tmp_token1);
	if (before_first_subshell_open)
		*mid = token_lst;
	tmp_token1 = tmp_token2;
	tmp_token2 = tmp_token2->next;
	ft_lstdelone(tmp_token1, free);
	*right = make_new_node(tmp_token2);
}

t_parse	*subshell_parsing(t_lex_lst *token_lst)
{
	t_parse	*root;

	root = ft_calloc(1, sizeof(t_parse));
	if (root == NULL)
		return (NULL);
	root->is_subshell = 1;
	split_by_subshell(token_lst, &root->left, &root->right, &root->node);
	return (root);
}

t_parse	*parse(t_lex_lst *token_lst)
{
	t_parse		*root;
	t_lex_lst	*operator;

	if (check_inner_syntax(token_lst))
		return (NULL);
	delete_useless_ifs(token_lst);
	operator = get_root_node(&token_lst);
	if (operator == NULL)
	{
		if (has_subshell(token_lst))
			return (subshell_parsing(token_lst));
		return (make_new_node(token_lst));
	}
	else
	{
		root = ft_calloc(1, sizeof(t_parse));
		if (root == NULL)
			return (NULL);
		root->node = operator;
		root->left = parse(get_left_start(token_lst, root->node));
		root->right = parse(get_right_start(root->node));
	}
	return (root);
}
