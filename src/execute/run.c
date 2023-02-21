/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:45:12 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/09 07:55:17 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "sys/wait.h"
#include "builtin.h"

extern char	**environ;

static int	do_child(char **argv)
{
	const t_builtin_func	builtin_func = builtin(argv);

	if (ft_strchr(argv[0], '/'))
		exit(execve(argv[0], argv, environ));
	if (builtin_func)
		exit(builtin_func(argv));
	// path
	if (access(argv[0], F_OK | X_OK) == 0)
		exit(execve(argv[0], argv, environ));
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

static int	execute(char **argv)
{
	pid_t					pid;
	int						wstatus;
	const t_builtin_func	builtin_func = builtin(argv);

	if (builtin_func)
		return (builtin_func(argv));
	pid = fork();
	if (pid == 0)
		return (do_child(argv));
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

void	run(const char *command)
{
	static int	exit_status = 0;
	char		*comment;
	char		**argv;
	int			argc;

	comment = ft_strchr(command, '#');
	if (comment)
		*comment = '\0';
	if (*command == '\0')
		return ;
	//	lexing
	//	parsing
	//	expansion
	//	redirection
	argv = ft_split(command, ' ');
	if (argv == NULL)
		exit_status = EXIT_FAILURE;
	else
		exit_status = execute(argv);
	argc = -1;
	while (argv[++argc])
		free(argv[argc]);
	free(argv);
}
