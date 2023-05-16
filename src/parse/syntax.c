/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:51:29 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/16 11:50:18 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_redirection_lex(t_s_lex *lex_data)
{
	return (lex_data->type == LEXEME_ADDFIE
		|| lex_data->type == LEXEME_INFILE
		|| lex_data->type == LEXEME_HEREDOC
		|| lex_data->type == LEXEME_OUTFILE);
}

static int	is_operator_lex(t_s_lex *lex_data)
{
	return (lex_data->type == LEXEME_PIPE
		|| lex_data->type == LEXEME_AND
		|| lex_data->type == LEXEME_OR);
}

/*
all func in this file,
return 1 at syntax error ditected
*/
static int	redirection_pair_match_error(t_lex_lst *node_lst)
{
	int		pair_flag;
	int		dquote_flag;
	t_s_lex	*lex_data;

	pair_flag = 0;
	dquote_flag = 0;
	while (node_lst)
	{
		lex_data = node_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0
			&& pair_flag == 0
			&& !is_redirection_lex(lex_data))
			return (1);
		else if (pair_flag == 1
			&& lex_data->type != LEXEME_STRING
			&& lex_data->type != LEXEME_WILDCARD
			&& lex_data->type != LEXEME_ENVIRONMENT)
			return (1);
		node_lst = node_lst->next;
		if (dquote_flag == 0)
			pair_flag ^= 1;
	}
	return (pair_flag);
}

static int	command_redirection_match_error(t_lex_lst *lex_lst)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	while (lex_lst)
	{
		lex_data = lex_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && is_redirection_lex(lex_data))
		{
			lex_lst = lex_lst->next;
			break ;
		}
		lex_lst = lex_lst->next;
	}
	return (redirection_pair_match_error(lex_lst));
}

int	is_syntax_error(t_parse *root)
{
	t_lex_lst	*lex_lst;
	t_s_lex		*lex_data;

	if (root->is_subshell)
	{
		if (root->node)
			return (1);
		if (root->right)
			return (redirection_pair_match_error(root->right->node));
	}
	else
	{
		if (root->right && is_syntax_error(root->right))
			return (1);
		lex_lst = root->node;
		lex_data = lex_lst->content;
		if (is_operator_lex(lex_data))
			return (root->left == 0 || root->right == 0);
		else
			return (command_redirection_match_error(lex_lst));
	}
	if (root->left && is_syntax_error(root->left))
		return (1);
	return (0);
}
