/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 11:35:23 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_and(t_env **table, t_parse *tree)
{
	int	status;

	status = execute(table, tree->left);
	if (status != EXIT_SUCCESS)
		return (status);
	return (execute(table, tree->right));
}

static int	_or(t_env **table, t_parse *tree)
{
	int	status;

	status = execute(table, tree->left);
	if (status == EXIT_SUCCESS)
		return (status);
	return (execute(table, tree->right));
}

static int	_subshell(t_env **table, t_parse *tree)
{
	pid_t			pid;
	int				status;
	t_pipex			*pipex;
	struct s_pipex	*content;

	pid = fork();
	if (pid == 0)
	{
		pipex = new_pipex(table, tree->right);
		if (pipex)
		{
			content = pipex->content;
			status = redirect(content->redirect);
			if (status == -1)
				exit(EXIT_FAILURE);
			ft_lstdelone(pipex, free_pipex);
		}
		exit(execute(table, tree->left));
	}
	return (waitpid_ignore_signal(pid));
}

static int	_pipe(t_env **table, t_parse *tree)
{
	int		status;
	t_pipex	*pipex;

	pipex = new_pipex(table, tree->left);
	while (tree->right && lexeme_type(tree->right->node) == LEXEME_PIPE)
	{
		tree = tree->right;
		ft_lstadd_back(&pipex, new_pipex(table, tree->left));
	}
	ft_lstadd_back(&pipex, new_pipex(table, tree->right));
	status = all_pipex(pipex);
	ft_lstclear(&pipex, free_pipex);
	return (status);
}

int	execute(t_env **table, t_parse *tree)
{
	int				status;
	t_pipex			*pipex;

	if (tree == NULL)
		status = EXIT_SUCCESS;
	else if (lexeme_type(tree->node) == LEXEME_AND)
		status = _and(table, tree);
	else if (lexeme_type(tree->node) == LEXEME_OR)
		status = _or(table, tree);
	else if (lexeme_type(tree->node) == LEXEME_PIPE)
		status = _pipe(table, tree);
	else if (tree->is_subshell)
		status = _subshell(table, tree);
	else
	{
		pipex = new_pipex(table, tree);
		status = all_pipex(pipex);
		ft_lstdelone(pipex, free_pipex);
	}
	return (status);
}
