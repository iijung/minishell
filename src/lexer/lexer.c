/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:28:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/12 23:32:36 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#ifdef DEBUG
# define DEBUG 1
#else
# define DEBUG 0
#endif

static void	debug(void *param)
{
	const struct s_content	*c = param;
	const char				*typename[] = {
		"STRING",
		"EOF",
		"IFS",
		"QUOTE",
		"DQUOTE",
		"OPERATOR",
		"WILDCARD",
		"ENVIRONMENT",
		"PARENTHESIS",
		"REDIRECTION"
	};

	if (DEBUG == 0)
		return ;
	if (c == NULL)
		printf("DEBUG:: content is NULL\n");
	else
		printf("DEBUG:: content [%x: %12s] len[%lu] data[%.*s]\n",
			c->type, typename[c->type], c->len, (int)c->len, c->data);
}

static void	add_token(t_list **lst, int type, size_t len, char *data)
{
	t_list	*token;

	token = ft_lstnew(NULL);
	if (token == NULL)
		return ;
	token->content = ft_calloc(1, sizeof(struct s_content));
	if (token->content == NULL)
	{
		ft_lstdelone(token, NULL);
		return ;
	}
	((struct s_content *)token->content)->type = type;
	((struct s_content *)token->content)->data = data;
	((struct s_content *)token->content)->len = len;
	ft_lstadd_back(lst, token);
}

static int	is_lexeme(char data)
{
	if (data == ' ' || ('\t' <= data && data <= '\r'))
		return (LEXEME_IFS);
	else if (data == '\0')
		return (LEXEME_EOF);
	else if (data == '\'')
		return (LEXEME_QUOTE);
	else if (data == '"')
		return (LEXEME_DQUOTE);
	else if (data == '*')
		return (LEXEME_WILDCARD);
	else if (data == '$')
		return (LEXEME_ENVIRONMENT);
	else if (data == '(' || data == ')')
		return (LEXEME_PARENTHESIS);
	else if (data == '<' || data == '>')
		return (LEXEME_REDIRECTION);
	else if (data == '&' || data == '|')
		return (LEXEME_OPERATOR);
	return (LEXEME_STRING);
}

static int	lex_token(t_list **lst, char *base)
{
	int		type;
	char	*curr;

	if (base == NULL)
		return (-1);
	while (*base)
	{
		type = is_lexeme(base[0]);
		curr = base + 1;
		while (type == LEXEME_IFS && is_lexeme(curr[0]) == LEXEME_IFS)
			curr++;
		while (type == LEXEME_STRING && is_lexeme(curr[0]) == LEXEME_STRING)
			curr++;
		if (type == LEXEME_REDIRECTION || type == LEXEME_OPERATOR)
			curr += (base[0] == curr[0]);
		add_token(lst, type, curr - base, base);
		base = curr;
	}
	return (0);
}

t_list	*lex(char *command)
{
	t_list	*tokens;

	errno = 0;
	tokens = NULL;
	if (lex_token(&tokens, command) < 0 || errno)
	{
		ft_lstclear(&tokens, free);
		ft_putstr_fd("minishell: lexing error\n", STDERR_FILENO);
		return (NULL);
	}
	ft_lstiter(tokens, debug);
	return (tokens);
}
