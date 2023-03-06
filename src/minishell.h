/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/07 06:43:26 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

#define ERORR -1
#define FALSE 0
#define TRUE 1
# define HASH_MAX	10

struct s_minishell
{
	int		exit_status;
	t_list	*environ[HASH_MAX];
};

#endif
