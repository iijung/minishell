/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/17 20:04:37 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "lexer.h"

int	main(void)
{
	char		*command;
	t_lex_token	*lst_token;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		lst_token = lexer(command);
		while (lst_token)
		{
			printf("type : %d\n", lst_token->type);
			if (lst_token->type == E_STRING || lst_token->type == E_DQUOTE || lst_token->type == E_SQUOTE)
			{
				printf("string : %s\n", lst_token->string);
			}
			printf("=================\n");
			lst_token = lst_token->next;
		}
		ft_lstclear((t_list **)&lst_token, free);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
