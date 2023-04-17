/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:34:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 07:15:03 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void	debug(void *param)
{
	size_t			i;
	char **const	env = env_gets(param);

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	free(env);
}

int	env_hash(char *key)
{
	if (key == NULL)
		return (0);
	return (*key % ENVIRON_HASH_MAX);
}

void	env_set(t_env **table, char *key, char *val)
{
	const int			hash = env_hash(key);
	char				*delimeter;
	t_list				*curr;
	struct s_environ	*env;

	if (table == NULL || key == NULL)
		return ;
	env = ft_calloc(1, sizeof(struct s_environ));
	ft_assert(env == NULL, __FILE__, __LINE__);
	env->val = ft_strdup(val);
	delimeter = ft_strchr(key, '=');
	if (delimeter)
		*delimeter = '\0';
	env->key = ft_strdup(key);
	ft_assert(env->key == NULL || env->val == NULL, __FILE__, __LINE__);
	env_unset(table, key);
	curr = ft_lstnew(env);
	ft_assert(curr == NULL, __FILE__, __LINE__);
	ft_lstadd_back(&table[hash], curr);
}

t_env	**env_load(void)
{
	int			i;
	t_env		**table;
	extern char	**environ;

	table = ft_calloc(ENVIRON_HASH_MAX, sizeof(t_env *));
	ft_assert(table == NULL, __FILE__, __LINE__);
	i = 0;
	while (environ && environ[i])
	{
		env_set(table, environ[i], environ[i]);
		++i;
	}
	ft_debug(debug, table);
	return (table);
}
