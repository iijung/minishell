/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:11:13 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/03/07 02:53:38 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_meta(const char *string)
{
	return (*string == '"' || *string == '\'' || *string == ')' \
			|| *string == '(' || *string == '|' || *string == '\0' \
			|| ft_strncmp(string, "&&", 2) == 0 || is_ifs(*string));
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

int	get_next_type(const char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (E_HEREDOC);
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (E_APPEND);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (E_OR);
	else if (ft_strncmp(input, "&&", 2) == 0)
		return (E_AND);
	else if (*input == '|')
		return (E_PIPE);
	else if (*input == '(')
		return (E_SUB_S);
	else if (*input == ')')
		return (E_SUB_E);
	else if (*input == '<')
		return (E_READ);
	else if (*input == '>')
		return (E_WRITE);
	else if (is_ifs(*input))
		return (E_IFS);
	else
		return (E_STRING);
}

void	skip_ifs(const char **string)
{
	while (is_ifs(**string))
		(*string)++;
}
