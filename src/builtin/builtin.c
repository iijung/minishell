/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:32:56 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/20 04:04:49 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin_func	builtin(char **argv)
{
	if (argv == NULL || argv[0] == NULL)
		return (NULL);
//	if (ft_strncmp(argv[0], "echo", 5) == 0)
//		return (builtin_echo);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd);
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd);
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export);
//	if (ft_strncmp(argv[0], "unset", 6) == 0)
//		return (builtin_unset);
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env);
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit);
	return (NULL);
}
