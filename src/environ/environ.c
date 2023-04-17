/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 05:34:50 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

char	**env_gets(t_env **table)
{
	size_t				i;
	size_t				count;
	char				**rtn;
	t_env				*curr;

	if (table == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while (i < ENVIRON_HASH_MAX)
		count += ft_lstsize(table[i++]);
	rtn = ft_calloc(count + 1, sizeof(char *));
	ft_assert(rtn == NULL, __FILE__, __LINE__);
	i = 0;
	count = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		curr = table[i++];
		while (curr)
		{
			rtn[count++] = ((struct s_environ *)(curr->content))->val;
			curr = curr->next;
		}
	}
	return (rtn);
}

char	*env_get(t_env **table, char *key)
{
	const int			hash = env_hash(key);
	struct s_environ	*env;
	t_env				*curr;

	if (table == NULL || key == NULL)
		return (NULL);
	curr = table[hash];
	while (curr)
	{
		env = curr->content;
		if (env && env->key && ft_strlen(env->key) == ft_strlen(key))
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
				return (env->val);
		}
		curr = curr->next;
	}
	return (NULL);
}
