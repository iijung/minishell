/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:45:12 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 07:08:44 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "sys/wait.h"
#include "builtin.h"

static int	do_child(t_env **table, char **argv)
{
	const t_builtin_func	builtin_func = builtin(argv);
	char **const			envp = env_gets(table);

	if (ft_strchr(argv[0], '/'))
		exit(execve(argv[0], argv, envp));
	if (builtin_func)
		exit(builtin_func(table, argv));
	// path
	if (access(argv[0], F_OK | X_OK) == 0)
		exit(execve(argv[0], argv, envp));
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(envp);
	exit(127);
}

static int	execute(t_env **table, char **argv)
{
	pid_t					pid;
	int						wstatus;
	const t_builtin_func	builtin_func = builtin(argv);

	if (builtin_func)
		return (builtin_func(table, argv));
	pid = fork();
	if (pid == 0)
		return (do_child(table, argv));
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

int	executor(t_env **table, const char *command)
{
	int				exit_status;
	char **const	argv = ft_split(command, ' ');
	int				argc;

	ft_assert(argv == NULL, __FILE__, __LINE__);
	exit_status = execute(table, argv);
	argc = 0;
	while (argv[argc])
		free(argv[argc++]);
	free(argv);
	return (exit_status);
}
