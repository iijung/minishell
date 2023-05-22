/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:32:56 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 10:54:15 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "sys/stat.h"
#include <errno.h>

extern int	builtin_pwd(void);
extern int	builtin_cd(t_env **table, int argc, char **argv);
extern int	builtin_echo(int argc, char **argv);
extern int	builtin_exit(t_env **table, int argc, char **argv);
extern int	builtin_export(t_env **table, int argc, char **argv);
extern int	builtin_unset(t_env **table, int argc, char **argv);
extern int	builtin_env(t_env **table, int argc, char **argv);

static char	*strjoin3(char *s1, char *s2, char *s3)
{
	char	*rtn;
	char	*tmp;

	rtn = ft_strjoin(s1, s2);
	tmp = rtn;
	rtn = ft_strjoin(tmp, s3);
	free(tmp);
	return (rtn);
}

static void	search_path(t_env **table, char **argv, char **envp)
{
	int			i;
	char		**sp;
	char		*execve_path;
	struct stat	st;

	sp = ft_split(env_get_val(table, "PATH"), ':');
	i = 0;
	while (sp && sp[i])
	{
		execve_path = strjoin3(sp[i], "/", argv[0]);
		if (stat(execve_path, &st) == 0)
			exit(execve(execve_path, argv, envp));
		free(sp[i++]);
	}
}

static int	no_builtin(t_env **table, char **argv)
{
	pid_t		pid;
	char		**envp;
	struct stat	st;

	pid = fork();
	if (pid)
		return (waitpid_ignore_signal(pid));
	envp = env_get_arr(table);
	if (ft_strchr(argv[0], '/') != NULL)
	{
		if (stat(argv[0], &st) == 0)
			execve(argv[0], argv, envp);
	}
	else
		search_path(table, argv, envp);
	perror(argv[0]);
	if (errno == EISDIR || errno == EACCES)
		exit(126);
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
