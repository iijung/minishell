/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:19:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/03 07:10:59 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	builtin_pwd(void)
{
	char *const	pwd = getcwd(NULL, 0);

	if (pwd == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
