/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:08:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/09 06:10:43 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>	//
#include <stdlib.h> //
#include "libft.h"
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

static int	cd_oldpwd(void)
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
	return (builtin_pwd());
}

int	builtin_cd(const char **argv)
{
	int		argc;

	argc = -1;
	while (argv[++argc])
		;
	if (argc == 1)
		return (cd_home());
	if (argc != 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (cd_oldpwd());
	if (chdir(argv[1]) == -1)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
