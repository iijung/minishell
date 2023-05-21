/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 05:19:40 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 23:00:36 by minjungk         ###   ########.fr       */
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
				printf("%s=%s\n", env->key, env->val);
			curr = curr->next;
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_env(t_env **table, int argc, char **argv)
{
	pid_t	pid;
	char	*delimeter;

	pid = fork();
	if (pid == 0)
	{
		argc = 0;
		while (argv[++argc])
		{
			delimeter = ft_strchr(argv[argc], '=');
			if (delimeter == NULL)
				break ;
			*delimeter = '\0';
			env_set(table, argv[argc], delimeter + 1);
		}
		if (argv[argc] == NULL)
			exit(_show(table));
		exit(builtin(table, argv + argc));
	}
	return (waitpid_ignore_signal(pid));
}
