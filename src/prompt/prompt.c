/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:10:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/06 03:43:18 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

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

static void	set_terminal(void)
{
	struct termios	term;

	rl_event_hook = event;
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static char	*get_readline(void)
{
	struct termios	term;
	char			*line;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	tcgetattr(STDIN_FILENO, &term);
	set_terminal();
	line = readline("minishell$ ");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (line);
}

char	*prompt(void)
{
	char	*line;
	char	*command;

	line = get_readline();
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	command = ft_strtrim(line, " ");
	if (command == NULL || *command == '\0')
	{
		free(command);
		return (NULL);
	}
	add_history(command);
	free(line);
	return (command);
}
