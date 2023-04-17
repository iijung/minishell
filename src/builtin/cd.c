/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:08:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 06:35:39 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	cd_home(void)
{
	const char *const	path = getenv("HOME");

	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	cd_oldpwd(t_env **table, const char **argv)
{
	const char *const	path = getenv("OLDPWD");

	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (builtin_pwd(table, argv));
}

int	builtin_cd(t_env **table, const char **argv)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		++argc;
	if (argc == 1)
		return (cd_home());
	if (argc != 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (cd_oldpwd(table, argv));
	if (chdir(argv[1]) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
