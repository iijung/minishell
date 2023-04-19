/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:44 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/19 22:34:11 by minjungk         ###   ########.fr       */
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
extern int		env_size(t_env **table);
extern t_env	**env_load(void);
extern void		env_clear(t_env ***table);
extern void		env_unset(t_env **table, char *key);
extern void		env_set(t_env **table, char *key, char *val);
extern void		env_free_arr(char **arr);
extern char		**env_get_arr(t_env **table);
extern char		*env_get_val(t_env **table, char *key);

#endif
