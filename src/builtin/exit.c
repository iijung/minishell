/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:37:34 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/17 14:04:45 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(t_env **table, int argc, char **argv)
{
	int	i;
	int	exit_status;

	if (table == NULL || argc < 0 || argv == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (argv && argv[1] && argv[1][i])
	{
		if (ft_isdigit(argv[1][i++]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	exit_status = EXIT_SUCCESS;
	if (argv && argv[1])
		exit_status = ft_atoi(argv[1]);
	if (argv && argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit(exit_status);
}
