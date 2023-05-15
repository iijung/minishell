/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/16 03:13:20 by minjungk         ###   ########.fr       */
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
		ft_lstadd_back(&pipex, new_pipex(table, tree->left));
		tree = tree->right;
	}
	ft_lstadd_back(&pipex, new_pipex(table, tree->right));
	status = run_pipex(pipex);
	ft_lstclear(&pipex, free_pipex);
	return (status);
}

int	_single(t_env **table, t_parse *tree)
{
	pid_t			pid;
	int				status;
	t_pipex			*pipex;
	struct s_pipex	*content;
	t_builtin_func	builtin_func;

	pipex = new_pipex(table, tree);
	if (pipex == NULL)
		return (EXIT_FAILURE);
	content = pipex->content;
	builtin_func = builtin(content->argv);
	if (builtin_func)
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

int	execute(t_env **table, t_parse *tree)
{
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
	return (_single(table, tree));
}
