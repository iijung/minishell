/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:32:56 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 00:07:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	builtin_pwd(void);
extern int	builtin_cd(t_env **table, int argc, char **argv);
extern int	builtin_echo(int argc, char **argv);
extern int	builtin_exit(t_env **table, int argc, char **argv);
extern int	builtin_export(t_env **table, int argc, char **argv);
extern int	builtin_unset(t_env **table, int argc, char **argv);
extern int	builtin_env(t_env **table, int argc, char **argv);

static int	no_builtin(t_env **table, char **argv)
{
	int		i;
	pid_t	pid;
	char	**sp;
	char	**envp;
	char	command[PATH_MAX];

	pid = fork();
	if (pid)
		return (waitpid_ignore_signal(pid));
	envp = env_get_arr(table);
	execve(argv[0], argv, envp);
	i = 0;
	sp = ft_split(env_get_val(table, "PATH"), ':');
	while (sp && sp[i])
	{
		ft_strlcpy(command, sp[i], PATH_MAX);
		ft_strlcat(command, "/", PATH_MAX);
		ft_strlcat(command, argv[0], PATH_MAX);
		execve(command, argv, envp);
		free(sp[i++]);
	}
	free(sp);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

int	builtin(t_env **table, char **argv)
{
	int	argc;

	argc = 0;
	while (argv && argv[argc])
		++argc;
	if (argc <= 0)
		return (EXIT_SUCCESS);
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(argc, argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(table, argc, argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(table, argc, argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(table, argc, argv));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(table, argc, argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(table, argc, argv));
	return (no_builtin(table, argv));
}
