/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:20:04 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 18:41:49 by minjungk         ###   ########.fr       */
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
	if (tree->is_subshell)
		content->subshell = tree;
	else
		set_pipex(tree->node, content);
	return (rtn);
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
