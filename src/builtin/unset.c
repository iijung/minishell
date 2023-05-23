/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:08:18 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 19:09:29 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(t_env **table, int argc, char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (argv[i] && i < argc)
	{
		if (env_invalid(argv[i]))
			ret = EXIT_FAILURE;
		else
			env_unset(table, argv[i]);
		++i;
	}
	if (ret == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	ft_putstr_fd("minishell: unset: not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
