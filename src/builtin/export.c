/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 03:20:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 23:48:41 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_show(t_env **table)
{
	int					i;
	struct s_environ	*env;
	t_env				*curr;

	i = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		curr = table[i++];
		while (curr)
		{
			env = curr->content;
			if (env && ft_strncmp(env->key, "?", 2) != 0)
				printf("declare -x %s=\"%s\"\n", env->key, env->val);
			curr = curr->next;
		}
	}
	return (EXIT_SUCCESS);
}

static int	_export(t_env **table, char *argv)
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

int	builtin_export(t_env **table, int argc, char **argv)
{
	int	i;

	if (argv[1] == NULL)
		return (_show(table));
	i = 1;
	while (argv[i] && i < argc)
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
