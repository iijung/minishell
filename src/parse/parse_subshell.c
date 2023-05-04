/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:29:52 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/04 15:03:25 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "lexer.h"

static t_list	*get_before_subshell(t_list *tokens, int type)
{
	int				dquote_flag;
	struct s_lexeme	*cur_token;

	dquote_flag = 0;
	if (tokens == NULL)
		return (NULL);
	while (tokens->next)
	{
		cur_token = tokens->next->content;
		if (cur_token->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && cur_token->type == type)
			return tokens;
		else
			tokens = tokens->next;
	}	
}

static t_list	*make_one_subshell_node(t_list *tokens)
{

}

t_parse	*make_subshell_nodes(t_list **tokens)
{
	struct s_lexeme	*first_token;
	t_list			*cursor;
	t_list			*before_open;
	t_list			*before_close;

	if (*tokens == NULL)
		return ;
	first_token = (*tokens)->content;
	if (first_token->type == LEXEME_PARENTHESIS_OPEN)
	{
		// 처음토큰에 ( 있는 경우 처리후 루프
	}
		
	while (1)
	{
		before_open = get_before_parenthesis(tokens, LEXEME_PARENTHESIS_OPEN);
		if (before_open == NULL)
			return;
		
	}
}