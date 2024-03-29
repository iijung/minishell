/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:28:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 00:44:52 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*add_token(t_lex_lst **lst, int type, size_t len, char *data)
{
	t_lex_lst		*token;
	struct s_lexeme	*lexeme;

	lexeme = ft_calloc(1, sizeof(struct s_lexeme));
	if (lexeme == NULL)
		return (NULL);
	lexeme->type = type;
	lexeme->data = data;
	lexeme->len = len;
	token = ft_lstnew(lexeme);
	if (token == NULL)
	{
		free(lexeme);
		return (NULL);
	}
	ft_lstadd_back(lst, token);
	return (data + len);
}

static enum e_lexeme	get_lexeme(char *data)
{
	enum e_lexeme	i;

	if (*data == ' ' || ('\t' <= *data && *data <= '\r'))
		return (LEXEME_IFS);
	i = 0;
	while (i < MAX_LEXEME)
	{
		if (g_lexeme[i].len)
		{
			if (ft_strncmp(data, g_lexeme[i].data, g_lexeme[i].len) == 0)
				return (g_lexeme[i].type);
		}
		++i;
	}
	return (LEXEME_STRING);
}

static char	*case_of_environment(
t_lex_lst **lst,
char **curr)
{
	char *const			base = *curr;
	const enum e_lexeme	type = get_lexeme(base);

	if ((*curr)[1] == '?')
		return (add_token(lst, type, 1, base + 1));
	if (ft_isalnum((*curr)[1]) == 0 && (*curr)[1] != '_')
		return (add_token(lst, LEXEME_STRING, 1, base));
	++(*curr);
	while (curr[0] && (ft_isalnum((*curr)[0]) || (*curr)[0] == '_'))
		++(*curr);
	return (add_token(lst, type, *curr - base - 1, base + 1));
}

static char	*lex_token(t_lex_lst **lst, char *curr, int *in_dquote_flag)
{
	char *const			base = curr;
	const enum e_lexeme	type = get_lexeme(base);

	if (type == LEXEME_ENVIRONMENT)
		return (case_of_environment(lst, &curr));
	else if (type == LEXEME_QUOTE && *in_dquote_flag == 0)
	{
		curr = ft_strchr(base + 1, g_lexeme[type].data[0]);
		if (curr == NULL)
			return (NULL);
		return (add_token(lst, LEXEME_STRING, curr - base - 1, base + 1) + 1);
	}
	else if (g_lexeme[type].len)
	{
		if (type == LEXEME_DQUOTE)
			*in_dquote_flag ^= 1;
		return (add_token(lst, type, g_lexeme[type].len, base));
	}
	while (curr[1] && type == get_lexeme(curr + 1))
		++curr;
	return (add_token(lst, type, curr + 1 - base, base));
}

t_lex_lst	*lex(char *command)
{
	t_lex_lst	*tokens;
	int			in_dquote_flag;

	in_dquote_flag = 0;
	tokens = NULL;
	while (command && *command)
		command = lex_token(&tokens, command, &in_dquote_flag);
	if (command == NULL)
	{
		ft_lstclear(&tokens, free);
		ft_putstr_fd("minishell: lexing error\n", STDERR_FILENO);
		return (NULL);
	}
	return (tokens);
}
