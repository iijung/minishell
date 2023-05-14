/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/15 04:50:51 by minjungk         ###   ########.fr       */
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

	pid = fork();
	if (pid == 0)
	{
//		_redirection(table, tree->node);
		exit(execute(table, tree->left));
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	execute(t_env **table, t_parse *tree)
{
	if (tree == NULL)
		return (EXIT_SUCCESS);
	if (tree->node && tree->node->content)
	{
		if (((struct s_lexeme *)(tree->node->content))->type == LEXEME_AND)
			return (_and(table, tree));
		if (((struct s_lexeme *)(tree->node->content))->type == LEXEME_OR)
			return (_or(table, tree));
	}
	if (tree->is_subshell)
		return (_subshell(table, tree));
	return (all_pipex(table, tree->node));
}
