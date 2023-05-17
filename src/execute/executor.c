/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/17 13:09:25 by jaemjeon         ###   ########.fr       */
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
	pid_t	pid;
	int		status;
	t_pipex	*pipex;

	pid = fork();
	if (pid == 0)
	{
		pipex = new_pipex(table, tree->right);
		ft_assert(pipex == NULL, __FILE__, __LINE__);
		redirect(pipex->content);
		ft_lstdelone(pipex, free_pipex);
		exit(execute(table, tree->left));
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static int	_pipe(t_env **table, t_parse *tree)
{
	int		status;
	t_pipex	*pipex;

	pipex = new_pipex(table, tree->left);
	while (tree->right
		&& tree->right->node
		&& tree->right->node->content
		&& lexeme_type(tree->right->node->content) == LEXEME_PIPE)
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
	char			*tmp;
	int				status;
	t_pipex			*pipex;

	if (tree == NULL)
		status = EXIT_SUCCESS;
	else if (tree->node && lexeme_type(tree->node->content) == LEXEME_AND)
		status = _and(table, tree);
	else if (tree->node && lexeme_type(tree->node->content) == LEXEME_OR)
		status = _or(table, tree);
	else if (tree->node && lexeme_type(tree->node->content) == LEXEME_PIPE)
		status = _pipe(table, tree);
	else if (tree->is_subshell)
		status = _subshell(table, tree);
	else
	{
		pipex = new_pipex(table, tree);
		status = all_pipex(pipex);
		ft_lstdelone(pipex, free_pipex);
	}
	tmp = ft_itoa(status);
	env_set(table, "?", tmp);
	free(tmp);
	return (status);
}
