/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:20:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/16 03:37:05 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_pipex	*new_pipex(t_env **table, t_parse *tree)
{
	t_pipex			*rtn;
	struct s_pipex	*content;

	if (tree == NULL)
		return (NULL);
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
	content->envp = table;
	set_pipex(tree->node, content);
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

int	all_pipex(t_pipex *pipex)
{
	pid_t			pid;
	int				status;
	struct s_pipex	*content;
	t_builtin_func	builtin_func;

	if (pipex == NULL)
		return (EXIT_FAILURE);
	content = pipex->content;
	builtin_func = builtin(content->argv);
	if (ft_lstsize(pipex) == 1 && builtin_func)
		return (builtin_func(content->envp, content->argc, content->argv));
	pid = fork();
	if (pid == 0)
		exit(run_pipex(pipex));
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
