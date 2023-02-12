/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 05:24:31 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/03 04:57:22 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# include "libft.h"
# include <stdio.h>

void	ft_debug(void (*f)(void *), void *param);
void	ft_assert(int condition, char *file, int line);
#endif