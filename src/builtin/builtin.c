/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:32:56 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/09 07:59:40 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

t_builtin_func	builtin(char **argv)
{
	t_builtin_func	ret;

	ret = NULL;
//	if (argv && ft_strncmp(argv[0], "echo", 5) == 0)
//		ret = builtin_echo;
	if (argv && ft_strncmp(argv[0], "cd", 3) == 0)
		ret = builtin_cd;
	else if (argv && ft_strncmp(argv[0], "pwd", 4) == 0)
		ret = builtin_pwd;
//	else if (argv && ft_strncmp(argv[0], "export", 7) == 0)
//		ret = builtin_export;
//	else if (argv && ft_strncmp(argv[0], "unset", 6) == 0)
//		ret = builtin_unset;
	else if (argv && ft_strncmp(argv[0], "env", 4) == 0)
		ret = builtin_env;
	else if (argv && ft_strncmp(argv[0], "exit", 5) == 0)
		ret = builtin_exit;
	return (ret);
}
