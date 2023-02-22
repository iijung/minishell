#include "lexer.h"
#include "libft.h"

int	is_ifs(char c)
{
	return (c == ' ' || c == '\t');
}

static void	skip_ifs(const char **string)
{
	while (is_ifs(**string))
		(*string)++;
}

// int	read_string_norm(const char **p_cursor)
// {
// 	while (!(**p_cursor == '"' || **p_cursor == '\'' || **p_cursor == ')' || \
// 		**p_cursor == '(' || **p_cursor == '|' || **p_cursor == '\0' || \
// 		ft_strncmp(*p_cursor, "&&", 2) == 0 || is_ifs(**p_cursor)))
// 	{
// 		(*p_cursor)++;
// 	}
// }

int	read_string_in_quote(const char **p_cursor, char quote)
{
	char	*next_cursor;

	next_cursor = ft_strchr(*p_cursor + 1, quote);
	if (next_cursor == NULL)
	{
		*p_cursor = next_cursor;
		return (E_READ_STRING_ERROR);
	}
	else
		*p_cursor = next_cursor + 1;
	next_cursor++;
	if (*next_cursor == '\'')
		return (E_READ_STRING_IN_SQUOTE);
	else if (*next_cursor == '"')
		return (E_READ_STRING_IN_DQUOTE);
	else if (*next_cursor == '|' || ft_strncmp(next_cursor, "&&", 2) == 0)
		return (E_READ_STRING_ACC);
	else
		return (E_READ_STRING_NORM);
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
	int token_type)
{
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	new_token->type = token_type;
	if (token_type == E_STRING)
	{
		new_token->string = ft_substr(s_str, 0, len);
		if (new_token->string == NULL)
			exit(errno);
	}
	if (token_type == E_ERROR)
		ft_lstadd_front((t_list **)lst_lex_token, (t_list *)new_token);
	else
		ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
}

void	read_string(const char **cursor, t_lex_token **lst_lex_token)
{
	const char			*s_str = *cursor;
	int					token_type;

	if (is_ifs(**cursor))
	{
		token_type = E_IFS;
		skip_ifs(cursor);
	}
	else if (**cursor == '"' || **cursor == '\'')
	{
		*cursor = ft_strchr(s_str + 1, **cursor);
		if (*cursor == NULL)
			token_type = E_ERROR;
		else
		{
			token_type = E_STRING;
			(*cursor)++;
		}
	}
	else
	{
		token_type = E_STRING;
		while (!(**cursor == '"' || **cursor == '\'' || **cursor == ')' ||
				 **cursor == '(' || **cursor == '|' || **cursor == '\0' ||
				 ft_strncmp(*cursor, "&&", 2) == 0 || is_ifs(**cursor)))
			(*cursor)++;
	}
	lex_add_token(lst_lex_token, s_str, *cursor - s_str, token_type);
}

void	read_operator(const char **input, t_lex_token **lst_lex_token, int type)
{
	t_lex_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lex_token));
	if (new_token == NULL)
		exit(errno);
	new_token->type = type;
	ft_lstadd_back((t_list **)lst_lex_token, (t_list *)new_token);
	if (type == E_AND || type == E_OR || type == E_APPEND || type == E_HEREDOC)
		(*input) += 2;
	else
		(*input) += 1;
}

static int	get_next_type(const char *input)
{
	if (*input == '|')
		return (E_PIPE);
	else if (*input == '(')
		return (E_SUB_S);
	else if (*input == ')')
		return (E_SUB_E);
	else if (*input == '<')
		return (E_READ);
	else if (*input == '>')
		return (E_WRITE);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (E_HEREDOC);
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (E_APPEND);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (E_OR);
	else if (ft_strncmp(input, "&&", 2) == 0)
		return (E_AND);
	else if (is_ifs(*input))
		return (E_IFS);
	else
		return (E_STRING);
}

t_lex_token	*lexer(const char *input)
{
	t_parse	info_parse;
	int		next_token_type;

	ft_memset(&info_parse, 0, sizeof(t_parse));
	while (input && *input)
	{
		next_token_type = get_next_type(input);
		if (next_token_type == E_STRING || next_token_type == E_IFS)
			read_string(&input, &(info_parse.lst_token));
		else
			read_operator(&input, &(info_parse.lst_token), next_token_type);
	}
	return (info_parse.lst_token);
}
