/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 03:20:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/20 05:10:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_export(t_env **table, const char *argv)
{
	char		*key;
	char		*val;
	char *const	delimeter = ft_strchr(argv, '=');

	if (delimeter == NULL)
		return (EXIT_FAILURE);
	key = ft_strndup(argv, delimeter - argv);
	val = ft_strdup(delimeter + 1);
	ft_assert(key == NULL || val == NULL, __FILE__, __LINE__);
	env_set(table, key, val);
	free(key);
	free(val);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_env **table, const char **argv)
{
	int	i;

	if (table == NULL || argv == NULL)
		return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		if (_export(table, argv[i]) == EXIT_FAILURE)
			break ;
		++i;
	}
	if (argv[i] == NULL)
		return (EXIT_SUCCESS);
	ft_putstr_fd("minishell: export: not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
