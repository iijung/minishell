/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:19:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/27 21:38:54 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	pwd[PATH_MAX + 1];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: PWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
