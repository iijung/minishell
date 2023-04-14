/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:28:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/15 04:19:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	is_ifs(char c);
extern int	is_meta(const char *string);
extern void	skip_ifs(const char **string);
extern int	get_next_type(const char *input);

static void	lex_add_token(
		t_lex_token **lst_lex_token,
		const char *s_str,
		int len,
		int token_type)
{
	const struct s_lexeme	*c = param;
	const char				*typename[] = {
	[LEXEME_STRING] = "STRING",
	[LEXEME_EOF] = "EOF",
	[LEXEME_IFS] = "IFS",
	[LEXEME_OR] = "OR",
	[LEXEME_AND] = "AND",
	[LEXEME_HEREDOC] = "HEREDOC",
	[LEXEME_ADDFILE] = "ADDFILE",
	[LEXEME_OUTFILE] = "OUTFILE",
	[LEXEME_INFILE] = "INFILE",
	[LEXEME_PIPE] = "PIPE",
	[LEXEME_QUOTE] = "QUOTE",
	[LEXEME_DQUOTE] = "DQUOTE",
	[LEXEME_WILDCARD] = "WILDCARD",
	[LEXEME_ENVIRONMENT] = "ENVIRONMENT",
	[LEXEME_PARENTHESIS_OPEN] = "PARENTHESIS_OPEN",
	[LEXEME_PARENTHESIS_CLOSE] = "PARENTHESIS_CLOSE"};

	if (DEBUG == 0 || c == NULL)
		return ;
	printf("DEBUG:: lexeme [%x: %12s] len[%lu] data[%.*s]\n",
		c->type, typename[c->type], c->len, (int)c->len, c->data);
}

static char	*add_token(t_list **lst, int type, size_t len, char *data)
{
	t_list			*token;
	struct s_lexeme	*lexeme;

	if (len == 0)
		return (data);
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

static void	read_meta(const char **input, t_lex_token **lst_lex_token, int type)
{
	char *const			base = curr;
	const enum e_lexeme	type = get_lexeme(base);

	if (type == LEXEME_QUOTE)
	{
		curr = ft_strchr(base + 1, g_lexeme[type].data[0]);
		if (curr == NULL)
			return (NULL);
		return (add_token(lst, LEXEME_STRING, curr - base - 1, base + 1) + 1);
	}
	if (type == LEXEME_ENVIRONMENT)
	{
		if (ft_isalnum(curr[1]) == 0)
			return (add_token(lst, LEXEME_STRING, 1, base));
		++curr;
		while (curr[0] && ft_isalnum(curr[0]))
			++curr;
		return (add_token(lst, type, curr - base - 1, base + 1));
	}
	if (g_lexeme[type].len)
		return (add_token(lst, type, g_lexeme[type].len, base));
	while (curr[1] && type == get_lexeme(curr + 1))
		++curr;
	return (add_token(lst, type, curr + 1 - base, base));
}

t_lex_token	*lexer(const char *input)
{
	t_lex_token	*lst_token;
	int			next_token_type;

	tokens = NULL;
	while (command && *command)
		command = lex_token(&tokens, command);
	if (command == NULL)
	{
		next_token_type = get_next_type(input);
		if (next_token_type == LEXEME_STRING)
			read_string(&input, &lst_token);
		else if (next_token_type == LEXEME_IFS)
		{
			skip_ifs(&input);
			lex_add_token(&lst_token, NULL, 0, LEXEME_IFS);
		}
		else
			read_meta(&input, &lst_token, next_token_type);
	}
	lex_add_token(&lst_token, NULL, 0, LEXEME_END);
	return (lst_token);
}
