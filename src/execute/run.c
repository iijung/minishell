/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:45:12 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/07 23:56:16 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "util.h"
# include "sys/wait.h"

extern char	**environ;

static int	do_child(const char *command)
{
	char	**argv;

	argv = ft_split(command, ' ');
	ft_assert(argv == NULL, __FILE__, __LINE__);
	if (ft_strchr(argv[0], '/'))
		exit(execve(argv[0], argv, environ));
	// builtin
	// path
	if (access(argv[0], F_OK | X_OK) == 0)
		exit(execve(argv[0], argv, environ));
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

static int	execute(const char *command)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == 0)
		return (do_child(command));
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

void	run(const char *command)
{
	static int	exit_status = 0;
	char		*comment;

	comment = ft_strchr(command, '#');
	if (comment)
		*comment = '\0';
	if (*command == '\0')
		return ;
	//	lexing
	//	parsing
	//	expansion
	//	redirection
	exit_status = execute(command);
}
