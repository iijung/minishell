/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:51:02 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/03 04:58:38 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "libft.h"

void	ft_assert(int condition, char *file, int line)
{
	const int	save_errno = errno;

	if (condition == 0)
	{
		errno = 0;
		return ;
	}
	ft_putstr_fd(file, 2);
	write(2, ":", 1);
	ft_putnbr_fd(line, 2);
	errno = save_errno;
	perror(":");
	exit(EXIT_FAILURE);
}
