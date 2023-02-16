#include "lexer.h"

int	is_ifs(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_ifs(const char **string)
{
	while (is_ifs(**string))
		(*string)++;
}

static char const	*find_strend(char const *cursor)
{
	while (*cursor != '|' && *cursor != '&' && \
			*cursor != '(' && *cursor != ')' && *cursor != '\0')
		cursor++;
	return (cursor - 1);
}

int	read_quote(const char *quote_start, t_lex_token **lst_lex_token)
{
	char		*quote_end;
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	quote_end = ft_strchr(quote_start + 1, *quote_start);
	if (quote_end == NULL)
	{
		new_token->type = E_ERROR;
		ft_lstadd_front((t_list **)lst_lex_token, (t_list *)new_token);
		return (0);
	}
	else
	{
		if (*quote_start == '"')
			new_token->type = E_DQUOTE;
		else
			new_token->type = E_SQUOTE;
		new_token->string = ft_substr(quote_start, 0, quote_end - quote_start + 1);
		if (new_token->string == NULL)
			exit(errno);
		ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
		return (quote_end - quote_start + 1);
	}
}

int	read_nonquote(const char *string_start, t_lex_token **lst_lex_token)
{
	char const	*string_end;
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	string_end = find_strend(string_start);
	if (string_end == NULL)
	{
		new_token->type = E_ERROR;
		ft_lstadd_front((t_list **)lst_lex_token, (t_list *)new_token);
		return (0);
	}
	else
	{
		new_token->type = E_STRING;
		new_token->string = ft_substr(string_start, 0, string_end - string_start + 1);
		if (new_token->string == NULL)
			exit(errno);
		ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
		return (string_end - string_start + 1);
	}

}

int	read_string(const char *cursor, t_lex_token **lst_lex_token)
{
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	if (*cursor == '"' || *cursor == '\'')
		return (read_quote(cursor, lst_lex_token));
	else
		return (read_nonquote(cursor, lst_lex_token));
}

int	read_operator(t_lex_token **lst_lex_token, int type)
{
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	new_token->type = type;
	ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
	if (type == E_PIPE || type == E_SUB_S || type == E_SUB_E)
		return (1);
	else if (type == E_AND || type == E_OR)
		return (2);
	else
		return (0);
}

t_lex_token	*lexer(const char *input)
{
	t_lex_token	*lst_lex_token;

	lst_lex_token = NULL;
	while (*input)
	{
		skip_ifs(&input);
		if (ft_strncmp(input, "||", 2) == 0)
			input += read_operator(&lst_lex_token, E_OR);
		else if (ft_strncmp(input, "&&", 2) == 0)
			input += read_operator(&lst_lex_token, E_AND);
		else if (*input == '|')
			input += read_operator(&lst_lex_token, E_PIPE);
		else if (*input == ')')
			input += read_operator(&lst_lex_token, E_SUB_E);
		else if (*input == '(')
			input += read_operator(&lst_lex_token, E_SUB_S);
		else
			input += read_string(input, &lst_lex_token);
	}
	return (lst_lex_token);
}
