/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:28:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/12 18:28:40 by minjungk         ###   ########.fr       */
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
	const struct s_lexeme	*c = param;
	const char				*typename[] = {
		"STRING",
		"EOF",
		"IFS",
		"QUOTE",
		"DQUOTE",
		"WILDCARD",
		"ENVIRONMENT",
		"PARENTHESIS_OPEN",
		"PARENTHESIS_CLOSE",
		"OR",
		"AND",
		"PIPE",
		"HEREDOC",
		"INFILE",
		"OUTFILE",
		"ADDFILE"};

	if (DEBUG == 0)
		return ;
	if (c == NULL)
		printf("DEBUG:: lexeme is NULL\n");
	else
		printf("DEBUG:: lexeme [%x: %12s] len[%lu] data[%.*s]\n",
			c->type, typename[c->type], c->len, (int)c->len, c->data);
}

static char	*add_token(t_list **lst, int type, size_t len, char *data)
{
	t_list			*token;
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
	else if (data == '(')
		return (LEXEME_PARENTHESIS_OPEN);
	else if (data == ')')
		return (LEXEME_PARENTHESIS_CLOSE);
	else if (data == '<')
		return (LEXEME_INFILE);
	else if (data == '>')
		return (LEXEME_OUTFILE);
	else if (data == '|')
		return (LEXEME_PIPE);
	return (LEXEME_STRING);
}

static char	*lex_token(t_list **lst, char *curr)
{
	char *const	base = curr;
	const int	type = is_lexeme(base[0]);

	if (ft_strncmp(base, "||", 2) == 0)
		return (add_token(lst, LEXEME_OR, 2, base));
	else if (ft_strncmp(base, "&&", 2) == 0)
		return (add_token(lst, LEXEME_AND, 2, base));
	else if (ft_strncmp(base, "<<", 2) == 0)
		return (add_token(lst, LEXEME_HEREDOC, 2, base));
	else if (ft_strncmp(base, ">>", 2) == 0)
		return (add_token(lst, LEXEME_ADDFILE, 2, base));
	if ((type == LEXEME_QUOTE && ft_strchr(base + 1, '\'') == NULL)
		&& (type == LEXEME_DQUOTE && ft_strchr(base + 1, '"') == NULL))
		errno = EINVAL;
	while (type == LEXEME_IFS && is_lexeme(curr[1]) == LEXEME_IFS)
		++curr;
	while (type == LEXEME_STRING && is_lexeme(curr[1]) == LEXEME_STRING)
		++curr;
	return (add_token(lst, type, curr + 1 - base, base));
}

t_list	*lex(char *command)
{
	t_list	*tokens;

	errno = 0;
	tokens = NULL;
	while (command && *command)
		command = lex_token(&tokens, command);
	if (command == NULL || errno)
	{
		ft_lstclear(&tokens, free);
		ft_putstr_fd("minishell: lexing error\n", STDERR_FILENO);
		return (NULL);
	}
	ft_lstiter(tokens, debug);
	return (tokens);
}
