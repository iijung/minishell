/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:25:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/23 00:10:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(int argc, char **argv)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		no_newline = 1;
		++i;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i != argc - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		++i;
	}
	if (no_newline == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
