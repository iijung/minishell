/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:37:34 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/20 03:38:00 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(t_env **table, const char **argv)
{
	int	exit_status;

	(void)table;
	exit_status = EXIT_SUCCESS;
	if (argv && argv[1])
		exit_status = ft_atoi(argv[1]);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv && argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(exit_status);
}
