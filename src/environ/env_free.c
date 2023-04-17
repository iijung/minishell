/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:05:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 07:14:09 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void	env_free(void *param)
{
	struct s_environ *const	env = param;

	if (env == NULL)
		return ;
	free(env->key);
	env->key = NULL;
	free(env->val);
	env->val = NULL;
	free(env);
}

void	env_unset(t_env **table, char *key)
{
	const int			hash = env_hash(key);
	t_env				*prev;
	t_env				*curr;
	struct s_environ	*env;

	if (table == NULL || key == NULL)
		return ;
	prev = NULL;
	curr = table[hash];
	while (curr)
	{
		env = curr->content;
		if (env && env->key
			&& ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			if (prev == NULL)
				table[hash] = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, env_free);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	env_clear(t_env ***table)
{
	int		i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		if ((*table)[i] != NULL)
		{
			ft_lstclear(&(*table)[i], env_free);
			(*table)[i] = NULL;
		}
		++i;
	}
	free(*table);
	*table = NULL;
}
