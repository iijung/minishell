/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/06 01:24:26 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute(t_pipex *pipex)
{
	pid_t			pid;
	int				status;
	struct s_pipex	*content;
	t_builtin_func	builtin_func;

	if (pipex == NULL)
		return (EXIT_FAILURE);
	if (ft_lstsize(pipex) == 1)
	{
		content = pipex->content;
		builtin_func = builtin(content->argv);
		if (builtin_func)
			return (builtin_func(content->envp, content->argc, content->argv));
	}
	pid = fork();
	if (pid == 0)
		exit(run_pipex(pipex));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
