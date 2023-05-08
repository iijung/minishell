/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:20:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/06 01:25:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_pipex	*_make(t_env **envp, char *command)
{
	int				argc;
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
	content->command = command;
	content->envp = envp;
	content->argv = ft_split(command, ' ');
	argc = 0;
	while (content->argv && content->argv[argc])
		++argc;
	content->argc = argc;
	return (rtn);
}

void	free_pipex(void *param)
{
	int						argc;
	struct s_pipex *const	content = param;

	if (content->in_fd != -1)
		close(content->in_fd);
	if (content->out_fd != -1)
		close(content->out_fd);
	content->in_fd = -1;
	content->out_fd = -1;
	argc = 0;
	while (content->argv && content->argv[argc])
		free(content->argv[argc++]);
	free(content->argv);
	content->argv = NULL;
	free(content);
}

//t_pipex	*new_pipex(t_env **table, t_parse *trees)
t_pipex	*new_pipex(t_env **envp, char *command)
{
	t_pipex	*rtn;
	t_pipex	*tmp;

	rtn = NULL;
	tmp = _make(envp, command);
	if (tmp == NULL)
	{
		ft_lstclear(&rtn, free_pipex);
		return (NULL);
	}
	ft_lstadd_back(&rtn, tmp);
	return (rtn);
}
