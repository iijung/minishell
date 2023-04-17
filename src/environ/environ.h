/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:44 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 05:39:27 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENVIRON_H
# define ENVIRON_H
# include "util.h"

# define ENVIRON_HASH_MAX	62

typedef t_list	t_env;

struct s_environ
{
	char	*key;
	char	*val;
};

extern int		env_hash(char *key);
extern void		env_clear(t_env ***table);
extern void		env_unset(t_env **table, char *key);
extern void		env_set(t_env **table, char *key, char *value);
extern char		*env_get(t_env **table, char *key);
extern char		**env_gets(t_env **table);
extern t_env	**env_load(void);

#endif
