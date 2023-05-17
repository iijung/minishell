/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:42:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/16 21:18:49 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_open(char *file, int flag)
{
	int		fd;
	int		count;
	t_list	*path;

	path = NULL;
	if (ft_strchr(file, '*') == NULL)
		fd = open(file, flag, 0666);
	else
	{
		path = get_wildcard(file);
		count = ft_lstsize(path);
		if (count != 1)
		{
			ft_putstr_fd(file, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		fd = open(path->content, flag, 0666);
		ft_lstclear(&path, free);
	}
	return (fd);
}

void	redirect(struct s_pipex *content)
{
	if (content->in_fd == -1 && content->infile)
		content->in_fd = _open(content->infile, O_RDONLY);
	if (content->in_fd != -1)
	{
		if (dup2(content->in_fd, STDIN_FILENO) == -1)
			ft_assert(1, __FILE__, __LINE__);
		close(content->in_fd);
		content->in_fd = -1;
	}
	if (content->outfile)
	{
		if (content->in_fd != -1)
			close(content->out_fd);
		content->out_fd = _open(content->outfile, content->outflag);
	}
	if (content->out_fd != -1)
	{
		if (dup2(content->out_fd, STDOUT_FILENO) == -1)
			ft_assert(1, __FILE__, __LINE__);
		close(content->out_fd);
		content->out_fd = -1;
	}
}

static void	_exec(void *param)
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
		redirect(content);
		exit(builtin_env(content->envp, content->argc, content->argv));
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

int	run_pipex(t_pipex *pipex)
{
	int				ret;
	const int		save_stdin = dup(STDIN_FILENO);
	const int		save_stdout = dup(STDOUT_FILENO);
	struct s_pipex	*last_content;

	ret = EXIT_FAILURE;
	if (save_stdin != -1 && save_stdout != -1)
	{
		last_content = ft_lstlast(pipex)->content;
		last_content->out_fd = save_stdout;
		{
			ft_lstiter(pipex, _exec);
			ft_lstiter(pipex, _wait);
			ret = last_content->exit_status;
		}
		dup2(save_stdout, STDOUT_FILENO);
		dup2(save_stdin, STDOUT_FILENO);
	}
	if (save_stdin != -1)
		close(save_stdin);
	if (save_stdout != -1)
		close(save_stdout);
	return (ret);
}
