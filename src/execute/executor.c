/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/05 18:56:09 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_exec(void *param)
{
	struct s_pipex *const	content = param;
	const t_builtin_func	builtin_func = builtin(content->argv);

	if (builtin_func)
		return (builtin_func(content->envp, content->argc, content->argv));
	content->pid = fork();
	if (content->pid == 0)
		exit(builtin_env(content->envp, content->argc, content->argv));
	waitpid(content->pid, &content->exit_status, 0);
	if (WIFSIGNALED(content->exit_status))
		return (128 + WTERMSIG(content->exit_status));
	return (WEXITSTATUS(content->exit_status));
}

int	execute(t_pipex *pipex)
{
	pid_t			pid;
	int				status;

	if (pipex == NULL)
		return (EXIT_FAILURE);
	if (ft_lstsize(pipex) == 1)
		return (_exec(pipex->content));
	pid = fork();
	if (pid == 0)
		exit(run_pipex(pipex));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
