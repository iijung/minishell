/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/04 23:46:41 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_status;

static void	handler(int sig)
{
	g_status = sig;
}

static int	event(void)
{
	if (g_status == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_status = 0;
	}
	return (0);
}

static void	loop(void)
{
	char	*line;
	char	*command;

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
}

int	main(void)
{
	struct termios	term_org;
	struct termios	term_new;

	rl_event_hook = event;
	signal(SIGINT, handler);
	tcgetattr(STDIN_FILENO, &term_org);
	tcgetattr(STDIN_FILENO, &term_new);
	term_new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term_new);
	loop();
	tcsetattr(STDIN_FILENO, TCSANOW, &term_org);
	exit(EXIT_SUCCESS);
}
