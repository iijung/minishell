/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:37:34 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 00:05:36 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(t_env **table, int argc, char **argv)
{
	int			i;
	char *const	exit_status = env_get_val(table, "?");

	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (127);
	}
	i = 0;
	while (argv[1] && argv[1][i])
	{
		if (ft_isdigit(argv[1][i++]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			break ;
		}
	}
	if (argv[1])
		exit(ft_atoi(argv[1]));
	if (exit_status == NULL)
		exit(EXIT_SUCCESS);
	exit(ft_atoi(exit_status));
}
