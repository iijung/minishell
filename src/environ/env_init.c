/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:34:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 17:27:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

#ifdef DEBUG
# define DEBUG 1
#else
# define DEBUG 0
#endif

extern char	**environ;

static void	debug(t_list **table, size_t table_max)
{
	size_t			i;
	char **const	environment = env_gets(table, table_max);

	i = -1;
	while (environment[++i])
		printf("%s\n", environment[i]);
	free(environment);
}

void	env_init(t_list **table, size_t table_max)
{
	int		i;
	char	*key;
	char	*delimeter;

	while (1)
	{
		i = -1;
		while (environ[++i])
		{
			delimeter = ft_strchr(environ[i], '=');
			if (delimeter == NULL)
				continue ;
			key = ft_strndup(environ[i], delimeter - environ[i]);
			env_insert(table, table_max, key, environ[i]);
			free(key);
		}
		debug(table, table_max);
		return ;
	}
	ft_putstr_fd("init error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
