/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:08:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 15:48:05 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

extern int	builtin_pwd(void);

static char	*_get_dirname(char *buf, char *prefix, char *path)
{
	ft_memset(buf, 0, PATH_MAX);
	ft_strlcpy(buf, prefix, PATH_MAX);
	ft_strlcat(buf, "/", PATH_MAX);
	ft_strlcat(buf, path, PATH_MAX);
	return (buf);
}

static void	_set_with_prefix(char *currpath, char *prefix, char *path)
{
	int			i;
	DIR			*dir;
	char		**sp;
	char		dirname[PATH_MAX];

	if (prefix == NULL)
		sp = ft_split("./", ':');
	else
		sp = ft_split(prefix, ':');
	i = 0;
	while (sp && sp[i])
	{
		if (currpath[0] == '\0')
		{
			dir = opendir(_get_dirname(dirname, sp[i], path));
			if (dir)
			{
				ft_strlcpy(currpath, dirname, PATH_MAX);
				closedir(dir);
			}
		}
		free(sp[i++]);
	}
	free(sp);
}

static int	_cd(t_env **table, char *path)
{
	char		oldpath[PATH_MAX];
	char		currpath[PATH_MAX];

	if (path == NULL || *path == '\0')
		return (EXIT_SUCCESS);
	getcwd(oldpath, PATH_MAX);
	ft_memset(currpath, 0, PATH_MAX);
	if (*path == '/'
		|| !ft_strncmp(path, ".", 2) || !ft_strncmp(path, "./", 2)
		|| !ft_strncmp(path, "..", 3) || !ft_strncmp(path, "../", 3))
		ft_strlcpy(currpath, path, PATH_MAX);
	else
		_set_with_prefix(currpath, env_get_val(table, "CDPATH"), path);
	if (chdir(currpath) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	env_set(table, "OLDPWD", oldpath);
	getcwd(oldpath, PATH_MAX);
	env_set(table, "PWD", oldpath);
	return (builtin_pwd());
}

int	builtin_cd(t_env **table, int argc, char **argv)
{
	char	*path;
	char	*key;

	if (argc != 1 && argc != 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argc == 2 && ft_strncmp(argv[1], "-", 2) != 0)
		return (_cd(table, argv[1]));
	key = "HOME";
	if (argc == 2)
		key = "OLDPWD";
	path = env_get_val(table, key);
	if (path)
		return (_cd(table, path));
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(" not set\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
