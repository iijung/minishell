/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:14:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/09 05:20:16 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef int	(*t_builtin_func)();

extern t_builtin_func	builtin(char **argv);
extern int				builtin_echo(const char **argv);
extern int				builtin_cd(const char **argv);
extern int				builtin_pwd(void);
extern int				builtin_export(const char **argv);
extern int				builtin_unset(const char **argv);
extern int				builtin_env(void);
extern int				builtin_exit(const char **argv);

#endif
