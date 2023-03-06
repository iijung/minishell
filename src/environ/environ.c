/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 17:28:19 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static void	destroy(void *param)
{
	struct s_environ *const	environment = param;

	if (environment == NULL)
		return ;
	free(environment->key);
	environment->key = NULL;
	free(environment->value);
	environment->value = NULL;
	free(environment);
}

int	env_delete(t_list **table, size_t table_max, char *key, int all)
{
	struct s_environ	*environment;
	t_list				*curr;
	t_list				*next;
	size_t				key_len;

	if (table == NULL || key == NULL)
		return (-1);
	curr = table[*key % table_max];
	key_len = 0;
	if (key)
		key_len = ft_strlen(key);
	while (curr && curr->next)
	{
		next = curr->next;
		environment = next->content;
		if (all || ft_strncmp(environment->key, key, key_len) == 0)
		{
			next = next->next;
			ft_lstdelone(curr->next, destroy);
			curr->next = next;
			continue ;
		}
		curr = next;
	}
	return (0);
}

int	env_insert(t_list **table, size_t table_max, char *key, char *value)
{
	struct s_environ	*environment;
	t_list				*curr;

	if (value == NULL || env_delete(table, table_max, key, 0) < 0)
		return (-1);
	while (1)
	{
		curr = ft_lstnew(NULL);
		if (curr == NULL)
			break ;
		curr->content = ft_calloc(1, sizeof(struct s_environ));
		if (curr->content == NULL)
			break ;
		environment = curr->content;
		environment->key = ft_strdup(key);
		environment->value = ft_strdup(value);
		if (environment->key == NULL || environment->value == NULL)
			break ;
		ft_lstadd_back(&table[*key % table_max], curr);
		return (0);
	}
	ft_lstdelone(curr, destroy);
	return (-1);
}

char	**env_gets(t_list **table, size_t table_max)
{
	char				**rtn;
	t_list				*curr;
	size_t				i;
	size_t				count;

	if (table == NULL)
		return (NULL);
	i = -1;
	count = 0;
	while (++i < table_max)
		count += ft_lstsize(table[i]);
	rtn = ft_calloc(count + 1, sizeof(char *));
	i = -1;
	count = 0;
	while (++i < table_max && rtn)
	{
		curr = table[i];
		while (curr)
		{
			rtn[count++] = ((struct s_environ *)(curr->content))->value;
			curr = curr->next;
		}
	}
	return (rtn);
}

char	*env_get(t_list **table, size_t table_max, char *key)
{
	struct s_environ	*environment;
	t_list				*curr;
	size_t				key_len;

	if (table == NULL || key == NULL)
		return (NULL);
	curr = table[*key % table_max];
	key_len = 0;
	if (key)
		key_len = ft_strlen(key);
	while (curr)
	{
		environment = curr->content;
		if (environment && ft_strncmp(environment->key, key, key_len) == 0)
			return (environment->value);
		curr = curr->next;
	}
	return (NULL);
}
