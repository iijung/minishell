#include "lexer.h"

int	is_ifs(char c)
{
	return (c == ' ' || c == '\t');
}

static void	skip_ifs(const char **string)
{
	while (is_ifs(**string))
		(*string)++;
}

int	read_string_norm(const char **p_cursor)
{
	while (!(**p_cursor == '"' || **p_cursor == '\'' || **p_cursor == ')' || \
		**p_cursor == '(' || **p_cursor == '|' || **p_cursor == '\0' || \
		ft_strncmp(*p_cursor, "&&", 2) == 0 || is_ifs(**p_cursor)))
	{
		(*p_cursor)++;
	}
	if (**p_cursor == '"')
		return (E_READ_STRING_IN_DQUOTE);
	else if (**p_cursor == '\'')
		return (E_READ_STRING_IN_SQUOTE);
	else
	{
		return (E_READ_STRING_ACC);
	}
}

int	read_string_in_quote(const char **p_cursor, char quote)
{
	char	*next_cursor;

	next_cursor = ft_strchr(*p_cursor + 1, quote);
	if (next_cursor == NULL)
		*p_cursor = next_cursor;
	else
		*p_cursor = next_cursor + 1;
	if (next_cursor == NULL)
		return (E_READ_STRING_ERROR);
	else
	{
		next_cursor++;
		if (*next_cursor == '\'')
			return (E_READ_STRING_IN_SQUOTE);
		else if (*next_cursor == '"')
			return (E_READ_STRING_IN_DQUOTE);
		else
			return (E_READ_STRING_ACC);
	}
}

int	set_read_string_state(char c)
{
	if (c == '\'')
		return (E_READ_STRING_IN_SQUOTE);
	else if (c == '"')
		return (E_READ_STRING_IN_DQUOTE);
	else
		return (E_READ_STRING_NORM);
}

void	lex_add_token(t_lex_token **lst_lex_token, const char *s_str, int len, \
	int read_state)
{
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	if (read_state == E_READ_STRING_ACC)
	{
		new_token->type = E_STRING;
		new_token->string = ft_substr(s_str, 0, len);
		if (new_token->string == NULL)
			exit(errno);
		ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
	}
	else
	{
		new_token->type = E_ERROR;
		ft_lstadd_front((t_list **)lst_lex_token, (t_list *)new_token);
	}
}

void	read_string(const char **cursor, t_lex_token **lst_lex_token)
{
	const char			*s_str = *cursor;
	int					read_state;

	read_state = set_read_string_state(**cursor);
	while (read_state != E_READ_STRING_ACC && read_state != E_READ_STRING_ERROR)
	{
		if (read_state == E_READ_STRING_NORM)
			read_state = read_string_norm(cursor);
		else if (read_state == E_READ_STRING_IN_DQUOTE)
			read_state = read_string_in_quote(cursor, '"');
		else if (read_state == E_READ_STRING_IN_SQUOTE)
			read_state = read_string_in_quote(cursor, '\'');
		else
			break ;
	}
	lex_add_token(lst_lex_token, s_str, *cursor - s_str, read_state);
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
	while (input && *input)
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
			read_string(&input, &lst_lex_token);
	}
	return (lst_lex_token);
}
