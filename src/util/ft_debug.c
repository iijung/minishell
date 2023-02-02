/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:47:58 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/03 04:57:43 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#ifdef DEBUG
# define DEBUG 1
#else
# define DEBUG 0
#endif

void	ft_debug(void (*f)(void *), void *param)
{
	if (f == NULL || DEBUG == 0)
		return ;
	write(STDOUT_FILENO, "=================== DEBUG ===================\n", 46);
	f(param);
	write(STDOUT_FILENO, "===================  END  ===================\n", 46);
}
