/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 03:27:05 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_exec(struct s_pipex *content)
{
	if (content == NULL)
		return (EXIT_FAILURE);
	if (content->redirect && redirect(content->redirect) == -1)
		return (EXIT_FAILURE);
	return (builtin(content->envp, content->argv));
}

static void	_fork(void *param)
{
	int						pipes[2];
	struct s_pipex *const	content = param;

	ft_assert(content == NULL, __FILE__, __LINE__);
	ft_assert(pipe(pipes) == -1, __FILE__, __LINE__);
	content->pid = fork();
	if (content->pid == 0)
	{
		close(pipes[0]);
		ft_assert(dup2(pipes[1], STDOUT_FILENO) == -1, __FILE__, __LINE__);
		close(pipes[1]);
		if (content->subshell)
			exit(execute(content->envp, content->subshell, 0));
		else
			exit(_exec(content));
	}
	else
	{
		close(pipes[1]);
		ft_assert(dup2(pipes[0], STDIN_FILENO) == -1, __FILE__, __LINE__);
		close(pipes[0]);
	}
}

static void	_wait(void *param)
{
	struct s_pipex *const	content = param;

	ft_assert(content == NULL, __FILE__, __LINE__);
	content->exit_status = waitpid_ignore_signal(content->pid);
}

static int	_run(t_pipex *pipex)
{
	const int				save_stdin = dup(STDIN_FILENO);
	struct s_pipex *const	last_content = ft_lstlast(pipex)->content;
	t_redirect *const		tmp = new_redirect(NULL, LEXEME_OUTFILE, NULL);
	struct s_redirect		*content;

	ft_assert(save_stdin == -1 || tmp == NULL, __FILE__, __LINE__);
	{
		content = tmp->content;
		content->fd = dup(STDOUT_FILENO);
		ft_lstadd_front(&last_content->redirect, tmp);
	}
	{
		ft_lstiter(pipex, _fork);
		ft_lstiter(pipex, _wait);
		dup2(save_stdin, STDIN_FILENO);
	}
	if (save_stdin != -1)
		close(save_stdin);
	return (last_content->exit_status);
}

int	all_pipex(t_pipex *pipex)
{
	pid_t			pid;
	int				status;
	int				save_fd[2];

	if (pipex == NULL)
		return (EXIT_FAILURE);
	if (ft_lstsize(pipex) == 1)
	{
		save_fd[STDIN_FILENO] = dup(STDIN_FILENO);
		save_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
		status = EXIT_FAILURE;
		if (save_fd[STDIN_FILENO] != -1 && save_fd[STDOUT_FILENO] != -1)
			status = _exec(pipex->content);
		dup2(save_fd[STDIN_FILENO], STDIN_FILENO);
		dup2(save_fd[STDOUT_FILENO], STDOUT_FILENO);
		close(save_fd[STDIN_FILENO]);
		close(save_fd[STDOUT_FILENO]);
		return (status);
	}
	pid = fork();
	if (pid == 0)
		exit(_run(pipex));
	return (waitpid_ignore_signal(pid));
}
