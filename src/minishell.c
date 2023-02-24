/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 17:36:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "prompt.h"
#include "lexer.h"

extern int	executor(const char *command);

static void	run(struct s_minishell *sh, char *command)
{
	t_list	*tokens;

	//	lexing
	tokens = lex(command);
	ft_lstclear(&tokens, free);
	//	parsing
	//	expansion
	//	redirection
	sh->exit_status = executor(command);
}

int	main(void)
{
	static struct s_minishell	sh;
	char						*command;

	env_init(sh.environ, HASH_MAX);
	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		run(&sh, command);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
