/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:44 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 17:23:51 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENVIRON_H
# define ENVIRON_H
# include "libft.h"
# include "util.h"
# include <stdio.h>

struct s_environ
{
	char	*key;
	char	*value;
};

void	env_init(t_list **table, size_t table_max);
int		env_delete(t_list **table, size_t table_max, char *key, int all);
int		env_insert(t_list **table, size_t table_max, char *key, char *value);
char	*env_get(t_list **table, size_t table_max, char *key);
char	**env_gets(t_list **table, size_t table_max);

#endif
