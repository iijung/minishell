/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:20:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/15 04:52:40 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_pipex	*_make(t_env **envp)
{
	t_pipex			*rtn;
	struct s_pipex	*content;

	content = ft_calloc(1, sizeof(struct s_pipex));
	rtn = ft_lstnew(content);
	if (rtn == NULL || content == NULL)
	{
		free(content);
		ft_lstdelone(rtn, NULL);
		return (NULL);
	}
	content->in_fd = -1;
	content->out_fd = -1;
	content->envp = envp;
	return (rtn);
}

void	free_pipex(void *param)
{
	struct s_pipex *const	content = param;

	if (content == NULL)
		return ;
	if (content->in_fd != -1)
		close(content->in_fd);
	if (content->out_fd != -1)
		close(content->out_fd);
	content->in_fd = -1;
	content->out_fd = -1;
	free(content->argv);
	content->argv = NULL;
	ft_lstclear(&content->argl, free);
	free(content->infile);
	content->infile = NULL;
	free(content->outfile);
	content->outfile = NULL;
	free(content);
}

t_pipex	*new_pipex(t_env **table, t_lex_lst *curr)
{
	t_pipex			*rtn;
	t_pipex			*pipex;

	rtn = NULL;
	pipex = NULL;
	while (curr)
	{
		pipex = _make(table);
		if (pipex == NULL)
		{
			ft_lstclear(&rtn, free_pipex);
			return (NULL);
		}
		curr = set_pipex(curr, pipex->content);
		ft_lstadd_back(&rtn, pipex);
	}
	return (rtn);
}

int	all_pipex(t_env **table, t_lex_lst *lexemes)
{
	pid_t			pid;
	int				status;
	t_pipex			*pipex;
	struct s_pipex	*content;
	t_builtin_func	builtin_func;

	pipex = new_pipex(table, lexemes);
	if (pipex == NULL)
		return (EXIT_FAILURE);
	content = pipex->content;
	builtin_func = builtin(content->argv);
	if (ft_lstsize(pipex) == 1 && builtin_func)
	{
		status = builtin_func(content->envp, content->argc, content->argv);
		ft_lstdelone(pipex, free_pipex);
		return (status);
	}
	pid = fork();
	if (pid == 0)
		exit(run_pipex(pipex));
	ft_lstdelone(pipex, free_pipex);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
