/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 20:08:02 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	_and(t_env **table, t_parse *tree, int is_first)
{
	int	status;

	status = execute(table, tree->left, is_first);
	if (status != EXIT_SUCCESS)
		return (status);
	return (execute(table, tree->right, is_first));
}

static int	_or(t_env **table, t_parse *tree, int is_first)
{
	int	status;

	status = execute(table, tree->left, is_first);
	if (status == EXIT_SUCCESS)
		return (status);
	return (execute(table, tree->right, is_first));
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
			if (content->argl)
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				exit(258);
			}
			status = redirect(content->redirect);
			if (status == -1)
				exit(EXIT_FAILURE);
			ft_lstdelone(pipex, free_pipex);
		}
		exit(execute(table, tree->left, 0));
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

int	execute(t_env **table, t_parse *tree, int is_first)
{
	int				status;
	t_pipex			*pipex;
	struct s_pipex	*content;

	if (tree == NULL)
		return (EXIT_SUCCESS);
	if (lexeme_type(tree->node) == LEXEME_AND)
		return (_and(table, tree, is_first));
	if (lexeme_type(tree->node) == LEXEME_OR)
		return (_or(table, tree, is_first));
	if (lexeme_type(tree->node) == LEXEME_PIPE)
		return (_pipe(table, tree));
	if (tree->is_subshell)
		return (_subshell(table, tree));
	pipex = new_pipex(table, tree);
	if (is_first && pipex && pipex->content)
	{
		content = pipex->content;
		if (content->argc == 2 && content->argv && content->argv[0]
			&& ft_strncmp(content->argv[0], "exit", 5) == 0)
			ft_putstr_fd("exit\n", STDERR_FILENO);
	}
	status = all_pipex(pipex);
	ft_lstdelone(pipex, free_pipex);
	return (status);
}
