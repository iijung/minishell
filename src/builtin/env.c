/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 05:19:40 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/09 05:25:05 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

extern char	**environ;

int	builtin_env(void)
{
	int	i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
	return (EXIT_SUCCESS);
}
