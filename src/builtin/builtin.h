/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:14:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/04/18 06:24:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "environ.h"

typedef int	(*t_builtin_func)();

extern t_builtin_func	builtin(char **argv);
extern int				builtin_cd(t_env **table, const char **argv);
extern int				builtin_pwd(t_env **table, const char **argv);
extern int				builtin_echo(t_env **table, const char **argv);
extern int				builtin_exit(t_env **table, const char **argv);
extern int				builtin_export(t_env **table, const char **argv);
extern int				builtin_unset(t_env **table, const char **argv);
extern int				builtin_env(t_env **table, const char **argv);

#endif
