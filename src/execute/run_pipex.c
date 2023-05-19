/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 21:01:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_exec(struct s_pipex *content)
{
	int				status;
	int				save_fd[2];
	t_builtin_func	builtin_func;

	status = EXIT_FAILURE;
	save_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	save_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (content
		&& save_fd[STDIN_FILENO] != -1
		&& save_fd[STDOUT_FILENO] != -1
		&& redirect(content->redirect) != -1)
	{
		builtin_func = builtin(content->argv);
		if (builtin_func)
			status = builtin_func(content->envp, content->argc, content->argv);
		else
			status = builtin_env(content->envp, content->argc, content->argv);
	}
	dup2(save_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(save_fd[STDOUT_FILENO], STDOUT_FILENO);
	if (save_fd[STDIN_FILENO] != -1)
		close(save_fd[STDIN_FILENO]);
	if (save_fd[STDOUT_FILENO] != -1)
		close(save_fd[STDOUT_FILENO]);
	return (status);
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
	waitpid(content->pid, &content->exit_status, 0);
	if (WIFSIGNALED(content->exit_status))
		content->exit_status = 128 + WTERMSIG(content->exit_status);
	else
		content->exit_status = WEXITSTATUS(content->exit_status);
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
	struct s_pipex	*content;

	if (pipex == NULL)
		return (EXIT_FAILURE);
	content = pipex->content;
	if (ft_lstsize(pipex) == 1 && builtin(content->argv))
	{
		if (ft_strncmp(content->argv[0], "exit", 5) == 0)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		return (_exec(content));
	}
	pid = fork();
	if (pid == 0)
		exit(_run(pipex));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
