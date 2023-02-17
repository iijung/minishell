/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:28:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/17 19:27:23 by minjungk         ###   ########.fr       */
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
		"WILDCARD",
		"ENVIRONMENT",
		"PARENTHESIS",
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
		printf("DEBUG:: content is NULL\n");
	else
		printf("DEBUG:: content [%x: %12s] len[%lu] data[%.*s]\n",
			c->type, typename[c->type], c->len, (int)c->len, c->data);
}

static void	add_token(t_list **lst, int type, size_t len, const char *data)
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
	int			type;
	const char	*base = curr;

	if (ft_strncmp(base, "||", 2) == 0)
		add_token(lst, LEXEME_OR, 2, base);
	else if (ft_strncmp(base, "&&", 2) == 0)
		add_token(lst, LEXEME_AND, 2, base);
	else if (ft_strncmp(base, "<<", 2) == 0)
		add_token(lst, LEXEME_HEREDOC, 2, base);
	else if (ft_strncmp(base, ">>", 2) == 0)
		add_token(lst, LEXEME_ADDFILE, 2, base);
	else
	{
		type = is_lexeme(base[0]);
		++curr;
		while (type == LEXEME_IFS && is_lexeme(curr[0]) == LEXEME_IFS)
			++curr;
		while (type == LEXEME_STRING && is_lexeme(curr[0]) == LEXEME_STRING)
			++curr;
		add_token(lst, type, curr - base, base);
		return (curr);
	}
	return (curr + 2);
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
