/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:08:01 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/05 04:37:22 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"
#include <_types.h>

#define MAX_TOKEN_COUNT 100

enum
{
	READ_WAIT,
	READ_IFS,
	READ_LETTER,
	READ_PIPE,
	READ_LOGIC_OR,
	READ_LOGIC_AND,
	READ_RED_OUT,
	READ_RED_APPEND,
	READ_RED_IN,
	READ_RED_HEREDOC,
	READ_IN_SQUOTE,
	READ_IN_DQUOTE
};

typedef struct s_parse_info
{
	int			parse_state;
	int			prev_parse_state;
	t_token		*lst_token;
}	t_parse_info;

void	init_parse_info(t_parse_info *parse_info)
{
	ft_memset(parse_info, 0, sizeof(t_parse_info));
	parse_info->lst_token = ft_calloc(MAX_TOKEN_COUNT, sizeof(t_token));
	if (parse_info->lst_token == NULL)
		exit(errno);
}

t_token	*tokenize(const char *input)
{
	t_parse_info	parse_info;

	init_parse_info(&parse_info);
	while (*input)
	{
		if (parse_info.parse_state == READ_WAIT)
		else if (parse_info.parse_state == READ_IFS)
		else if (parse_info.parse_state == READ_LETTER)
		else if (parse_info.parse_state == READ_PIPE)
		else if (parse_info.parse_state == READ_AND)
		else if (parse_info.parse_state == READ_LOGIC_OR)
		else if (parse_info.parse_state == READ_LOGIC_AND)
		else if (parse_info.parse_state == READ_RED_OUT)
		else if (parse_info.parse_state == READ_RED_APPEND)
		else if (parse_info.parse_state == READ_RED_IN)
		else if (parse_info.parse_state == READ_RED_HEREDOC)
		else if (parse_info.parse_state == READ_IN_SQUOTE)
		else if (parse_info.parse_state == READ_IN_DQUOTE)
		else
	}
}

t_token	*parse(const char *input)
{
	t_token	*lst_token;
	int		parse_state;

	parse_state = READ_WAIT;
	lst_token = tokenize(input);
}
