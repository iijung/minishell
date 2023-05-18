/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:20:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/18 11:54:01 by jaemjeon         ###   ########.fr       */
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
	content->envp = table;
	set_pipex(tree->node, content);
	return (rtn);
}

static void	free_redirect(void *param)
{
	struct s_redirect_data *const	redirect_data = param;

	if (redirect_data->fd != -1)
		close(redirect_data->fd);
	redirect_data->fd = -1;
	free(redirect_data->filename);
	redirect_data->filename = NULL;
	free(redirect_data);
}

void	free_pipex(void *param)
{
	struct s_pipex *const	content = param;

	if (content == NULL)
		return ;
	free(content->argv);
	content->argv = NULL;
	ft_lstclear(&content->argl, free);
	ft_lstclear(&content->redirect, free_redirect);
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
	{
		if (ft_strncmp(content->argv[0], "exit", 5) == 0)
			ft_putstr_fd("exit\n", STDERR_FILENO);
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
