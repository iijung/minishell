/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:12:27 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 03:45:14 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

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
	else if (token_type == E_DQUOTE || token_type == E_SQUOTE)
	{
		new_token->string = ft_substr(s_str, 1, len - 2);
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
	const char	*s_str = *cursor;
	int			token_type;

	if (**cursor == '"' || **cursor == '\'')
	{
		*cursor = ft_strchr(s_str + 1, **cursor);
		if (*cursor == NULL)
			token_type = E_ERROR;
		else
		{
			if (*s_str == '"')
				token_type = E_DQUOTE;
			else
				token_type = E_SQUOTE;
			(*cursor)++;
		}
	}
	else
	{
		token_type = E_STRING;
		while (!(is_meta(*cursor) || **cursor == '\0' || is_ifs(**cursor)))
			(*cursor)++;
	}
	lex_add_token(lst_lex_token, s_str, *cursor - s_str, token_type);
}

void	read_meta(const char **input, t_lex_token **lst_lex_token, int type)
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

t_lex_token	*lexer(const char *input)
{
	t_lex_token	*lst_token;
	int			next_token_type;

	lst_token = NULL;
	while (input && *input)
	{
		next_token_type = get_next_type(input);
		if (next_token_type == E_STRING)
			read_string(&input, &lst_token);
		else if (next_token_type == E_IFS)
		{
			skip_ifs(&input);
			lex_add_token(&lst_token, NULL, 0, E_IFS);
		}
		else
			read_meta(&input, &lst_token, next_token_type);
	}
	lex_add_token(&lst_token, NULL, 0, E_END);
	return (lst_token);
}
