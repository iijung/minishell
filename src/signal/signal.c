/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:32:17 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/13 22:13:40 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline.h"
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t    g_status;

static void signal_handler(int signo)
{
    g_status = signo;
}

static int	signal_event(void)
{
	if (g_status == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_status = 0;
	}
	return (0);
}

void	setting_signal(int option)
{
	if (option == MINISHELL_NO_CHILD)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		rl_event_hook = signal_event;
	}
	else if (option == MINISHELL_HAS_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (option == EXE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}