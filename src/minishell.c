/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/06 05:34:54 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "lexer.h"
#include "parse.h"

int	main(void)
{
	char			*command;
	t_lex_token		*token_loop;
	t_lex_token		*lst_token;
	t_parse_tree	*tree_parse;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		lst_token = lexer(command);
		token_loop = lst_token;
		while (token_loop)
		{
			printf("type : %d\n", token_loop->type);
			if (token_loop->type == E_STRING || token_loop->type == E_DQUOTE || token_loop->type == E_SQUOTE)
			{
				printf("string : %s\n", token_loop->string);
			}
			printf("=================\n");
			token_loop = token_loop->next;
		}
		tree_parse = parse(lst_token);

		ft_lstclear((t_list **)&lst_token, free);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
