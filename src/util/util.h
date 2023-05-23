/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 05:24:31 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/20 23:22:27 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# include "libft.h"
# include <stdio.h>

extern void	ft_debug(void (*f)(void *), void *param);
extern void	ft_assert(int condition, char *file, int line);
extern char	*ft_strndup(const char *s1, size_t n);

extern int	waitpid_ignore_signal(pid_t pid);
#endif
