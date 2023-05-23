/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 03:20:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/23 00:32:27 by minjungk         ###   ########.fr       */
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
	if (env_invalid(key))
	{
		free(key);
		return (EXIT_FAILURE);
	}
	val = ft_strdup(delimeter + 1);
	if (val)
		env_set(table, key, val);
	free(key);
	free(val);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_env **table, int argc, char **argv)
{
	int	i;
	int	ret;

	if (argv[1] == NULL)
		return (_show(table));
	ret = EXIT_SUCCESS;
	i = 1;
	while (argv[i] && i < argc)
	{
		if (_export(table, argv[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		++i;
	}
	if (ret == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	ft_putstr_fd("minishell: export: not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
