/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 16:10:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "lexer.h"

extern int	executor(const char *command);

static void	run(char *command)
{
	t_list	*tokens;

	//	lexing
	tokens = lex(command);
	ft_lstclear(&tokens, free);
	//	parsing
	//	expansion
	//	redirection
	executor(command);
}

int	main(void)
{
	char	*command;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		run(command);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
