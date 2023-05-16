/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/16 21:30:47 by minjungk         ###   ########.fr       */
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
		pipex = new_pipex(table, tree);
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
	int				status;
	t_pipex			*pipex;

	if (tree == NULL)
		return (EXIT_SUCCESS);
	if (tree->node && lexeme_type(tree->node->content) == LEXEME_AND)
		return (_and(table, tree));
	if (tree->node && lexeme_type(tree->node->content) == LEXEME_OR)
		return (_or(table, tree));
	if (tree->node && lexeme_type(tree->node->content) == LEXEME_PIPE)
		return (_pipe(table, tree));
	if (tree->is_subshell)
		return (_subshell(table, tree));
	pipex = new_pipex(table, tree);
	status = all_pipex(pipex);
	ft_lstdelone(pipex, free_pipex);
	return (status);
}
