/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:08:18 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/27 21:44:06 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_unset(t_env **table, char *key)
{
	size_t		i;

	if (key == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (EXIT_FAILURE);
		++i;
	}
	env_unset(table, (char *)key);
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_env **table, int argc, char **argv)
{
	int	i;

	if (table == NULL || argc < 0 || argv == NULL)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i] && i < argc)
	{
		if (_unset(table, argv[i]) == EXIT_FAILURE)
			break ;
		++i;
	}
	if (argv[i] == NULL)
		return (EXIT_SUCCESS);
	ft_putstr_fd("minishell: unset: not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
