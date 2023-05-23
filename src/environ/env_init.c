/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:34:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/17 00:29:50 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void	debug(void *param)
{
	int						i;
	t_env **const			table = param;
	struct s_environ		*env;
	t_env					*curr;

	i = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		curr = table[i++];
		while (curr)
		{
			env = curr->content;
			if (env)
				printf("%s=%s\n", env->key, env->val);
			curr = curr->next;
		}
	}
}

int	env_hash(char *key)
{
	if (key == NULL)
		return (0);
	return (*key % ENVIRON_HASH_MAX);
}

int	env_size(t_env **table)
{
	int	i;
	int	count;

	if (table == NULL)
		return (0);
	i = 0;
	count = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		count += ft_lstsize(table[i++]);
	}
	return (count);
}

void	env_set(t_env **table, char *key, char *val)
{
	const int			hash = env_hash(key);
	t_list				*curr;
	struct s_environ	*env;

	if (table == NULL || key == NULL || val == NULL)
		return ;
	env = ft_calloc(1, sizeof(struct s_environ));
	ft_assert(env == NULL, __FILE__, __LINE__);
	env->key = ft_strdup(key);
	env->val = ft_strdup(val);
	ft_assert(env->key == NULL || env->val == NULL, __FILE__, __LINE__);
	env_unset(table, key);
	curr = ft_lstnew(env);
	ft_assert(curr == NULL, __FILE__, __LINE__);
	ft_lstadd_back(&table[hash], curr);
}

t_env	**env_load(void)
{
	int			i;
	char		*delimeter;
	t_env		**table;
	extern char	**environ;

	table = ft_calloc(ENVIRON_HASH_MAX, sizeof(t_env *));
	ft_assert(table == NULL, __FILE__, __LINE__);
	i = 0;
	while (environ && environ[i])
	{
		delimeter = ft_strchr(environ[i], '=');
		ft_assert(delimeter == NULL, __FILE__, __LINE__);
		*delimeter = '\0';
		env_set(table, environ[i], delimeter + 1);
		++i;
	}
	env_set(table, "?", "0");
	ft_debug(debug, table);
	return (table);
}
