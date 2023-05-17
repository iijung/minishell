/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 05:19:40 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/17 15:57:51 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "sys/wait.h"

static int	_show(t_env **table)
{
	int					i;
	struct s_environ	*env;
	t_env				*curr;

	i = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		curr = table[i++];
		while (curr)
		{
			env = curr->content;
			if (env && ft_strncmp(env->key, "?", 2) != 0)
				printf("%s=%s\n", env->key, env->val);
			curr = curr->next;
		}
	}
	return (EXIT_SUCCESS);
}

static int	_error(char *command)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	_exec_with_path(char *path, char **argv, char **envp)
{
	int				i;
	int				is_valid;
	char			**sp;
	char			command[PATH_MAX];

	if (path == NULL || access(argv[0], F_OK | X_OK) == 0)
		return (execve(argv[0], argv, envp));
	i = 0;
	is_valid = 0;
	sp = ft_split(path, ':');
	while (sp && sp[i])
	{
		if (is_valid == 0)
		{
			ft_strlcpy(command, sp[i], PATH_MAX);
			ft_strlcat(command, "/", PATH_MAX);
			ft_strlcat(command, argv[0], PATH_MAX);
			is_valid = access(command, F_OK | X_OK) == 0;
		}
		free(sp[i++]);
	}
	free(sp);
	if (is_valid == 0)
		return (_error(argv[0]));
	return (execve(command, argv, envp));
}

static int	_env(t_env **table, char **argv)
{
	int				i;
	int				status;
	char			*delimeter;
	char			**envp;
	char *const		path = env_get_val(table, "PATH");

	i = 0;
	while (argv[i])
	{
		delimeter = ft_strchr(argv[i], '=');
		if (delimeter == NULL)
			break ;
		*delimeter = '\0';
		env_set(table, argv[i++], delimeter + 1);
	}
	envp = env_get_arr(table);
	if (argv[i] == NULL || argv[i + 1] == NULL)
		status = _show(table);
	else
		status = _exec_with_path(path, argv + i, envp);
	env_free_arr(envp);
	return (status);
}

int	builtin_env(t_env **table, int argc, char **argv)
{
	pid_t	pid;
	int		wstatus;

	if (table == NULL || argc < 0 || argv == NULL)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		exit(_env(table, argv));
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		perror("minishell: env: ");
		return (128 + WTERMSIG(wstatus));
	}
	return (WEXITSTATUS(wstatus));
}
