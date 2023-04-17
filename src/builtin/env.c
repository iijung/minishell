/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 05:19:40 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 06:37:47 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_env **table, const char **argv)
{
	int				i;
	char **const	envp = env_gets(table);

	(void)argv;
	i = 0;
	while (envp && envp[i])
	{
		printf("%s\n", envp[i++]);
	}
	free(envp);
	return (EXIT_SUCCESS);
}
