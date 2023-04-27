/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:25:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/27 21:34:59 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(t_env **table, int argc, char **argv)
{
	int	i;
	int	no_newline;

	(void)table;
	i = 1;
	no_newline = 0;
	if (ft_strncmp(argv[i], "-n", 3) == 0)
	{
		no_newline = 1;
		++i;
	}
	while (i < argc)
	{
		if (i == argc - 1)
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		++i;
	}
	if (no_newline == 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
