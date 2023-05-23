/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 23:00:24 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char	*_join_key_val(char *key, char *val)
{
	char	*rtn;
	size_t	key_len;
	size_t	val_len;

	if (key == NULL || val == NULL)
		return (NULL);
	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	rtn = ft_calloc(key_len + val_len + 2, sizeof(char));
	ft_assert(rtn == NULL, __FILE__, __LINE__);
	ft_memmove(rtn, key, key_len);
	rtn[key_len] = '=';
	ft_memmove(rtn + key_len + 1, val, val_len);
	return (rtn);
}

int	env_invalid(char *key)
{
	int	i;

	if (key == NULL)
		return (EXIT_FAILURE);
	if (ft_isalpha(key[0]) == 0 && key[0] != '_')
		return (EXIT_FAILURE);
	i = 0;
	while (key[++i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	env_free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**env_get_arr(t_env **table)
{
	int					i;
	int					count;
	char				**rtn;
	struct s_environ	*env;
	t_env				*curr;

	if (table == NULL)
		return (NULL);
	count = env_size(table);
	rtn = ft_calloc(count + 1, sizeof(char *));
	ft_assert(rtn == NULL, __FILE__, __LINE__);
	i = 0;
	count = 0;
	while (i < ENVIRON_HASH_MAX)
	{
		curr = table[i++];
		while (curr)
		{
			env = curr->content;
			if (env && ft_strncmp(env->key, "?", 2) != 0)
				rtn[count++] = _join_key_val(env->key, env->val);
			curr = curr->next;
		}
	}
	return (rtn);
}

char	*env_get_val(t_env **table, char *key)
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
