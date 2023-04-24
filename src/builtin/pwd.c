/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:19:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/23 16:58:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_env **table, const char **argv)
{
	char	pwd[PATH_MAX + 1];

	(void)table;
	(void)argv;
	ft_assert(getcwd(pwd, sizeof(pwd)) == NULL, __FILE__, __LINE__);
	printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
