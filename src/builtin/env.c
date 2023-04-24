/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 05:19:40 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/24 17:33:49 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_env **table, int argc, char **argv)
{
	int		i;
	char	**envp;

	(void)argc;
	(void)argv;
	if (table == NULL)
		return (EXIT_FAILURE);
	envp = env_get_arr(table);
	if (envp == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	env_free_arr(envp);
	return (EXIT_SUCCESS);
}
