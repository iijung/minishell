/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:08:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/24 16:32:08 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

static int	_can_change_path(char *cdpath, const char *path)
{
	size_t			len;
	DIR				*dir;
	struct dirent	*dirent;
	char			dirname[PATH_MAX];

	dir = opendir(cdpath);
	len = ft_strlcpy(dirname, path, sizeof(dirname));
	if (len > 0 && dirname[len - 1] == '/')
		dirname[len - 1] = '\0';
	while (dir)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		if (dirent->d_type == DT_DIR
			&& ft_strlen(dirent->d_name) == ft_strlen(dirname)
			&& ft_strncmp(dirent->d_name, dirname, ft_strlen(dirname)) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static void	_set_with_cdpath(char *currpath, t_env **table, const char *path)
{
	int			i;
	char		**sp;
	char *const	cdpath = env_get_val(table, "CDPATH");

	ft_memset(currpath, 0, PATH_MAX);
	if (cdpath == NULL)
		sp = ft_split(".", ':');
	else
		sp = ft_split(cdpath, ':');
	i = 0;
	while (sp && sp[i])
	{
		if (currpath[0] == '\0' && _can_change_path(sp[i], path))
		{
			ft_strlcpy(currpath, sp[i], PATH_MAX);
			ft_strlcat(currpath, "/", PATH_MAX);
			ft_strlcat(currpath, path, PATH_MAX);
		}
		free(sp[i++]);
	}
	free(sp);
}

static int	_cd(t_env **table, const char *path)
{
	char		oldpath[PATH_MAX];
	char		currpath[PATH_MAX];

	if (path == NULL)
		path = env_get_val(table, "HOME");
	if (path == NULL || *path == '\0')
		return (EXIT_FAILURE);
	if (*path == '/'
		|| !ft_strncmp(path, ".", 2) || !ft_strncmp(path, "./", 2)
		|| !ft_strncmp(path, "..", 3) || !ft_strncmp(path, "../", 3))
		ft_strlcpy(currpath, path, PATH_MAX);
	else
		_set_with_cdpath(currpath, table, path);
	getcwd(oldpath, PATH_MAX);
	if (chdir(currpath) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	env_set(table, "OLDPWD", oldpath);
	getcwd(oldpath, PATH_MAX);
	env_set(table, "PWD", oldpath);
	return (builtin_pwd(table, NULL));
}

int	builtin_cd(t_env **table, const char **argv)
{
	int		argc;
	char	*path;
	char	*key;

	argc = 0;
	while (argv && argv[argc])
		++argc;
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
	ft_putstr_fd("minishell: cd: \n", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(" not set\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
