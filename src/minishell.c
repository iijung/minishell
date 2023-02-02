/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/03 06:36:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_status;

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		g_status = 0;
	}
}

int	main(void)
{
	char	*line;
	char	*command;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		command = ft_strtrim(line, " ");
		if (command && *command)
		{
			add_history(command);
			printf("[TODO] execute[%s]\n", command);
		}
		free(command);
		free(line);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
