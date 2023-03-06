/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:07:31 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/24 17:20:59 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*rtn;

	i = ft_strlen(s1);
	if (i < n)
		n = i;
	rtn = ft_calloc(n + 1, sizeof(char));
	if (rtn == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
		rtn[i] = s1[i];
	return (rtn);
}
