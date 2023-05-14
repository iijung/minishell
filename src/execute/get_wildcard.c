/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:55:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/14 19:35:57 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include <dirent.h>

static char	*_extract_word(char *pattern)
{
	size_t	i;
	size_t	len;
	char	*rtn;

	len = 0;
	while (pattern && pattern[len] != '\0' && pattern[len] != '*')
		++len;
	rtn = ft_calloc(len + 1, sizeof(char));
	if (rtn == NULL)
		return (NULL);
	i = 0 ;
	while (i < len)
	{
		rtn[i] = pattern[i];
		++i;
	}
	return (rtn);
}

static int	_is_match(char *pattern, char *str)
{
	char	*word;

	while (*pattern)
	{
		if (*pattern == *str)
		{
			++pattern;
			++str;
		}
		else if (*pattern == '*')
		{
			++pattern;
			word = _extract_word(pattern);
			if (word == NULL)
				return (0);
			str = ft_strnstr(str, word, ft_strlen(str));
			free(word);
			if (str == NULL)
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

static char	*_concat(char **rtn, char *str)
{
	size_t	slen[2];
	size_t	dlen;
	char	*dst;

	if (*rtn == NULL && str != NULL)
		*rtn = ft_strdup(str);
	else if (*rtn && str)
	{
		slen[0] = ft_strlen(*rtn);
		slen[1] = ft_strlen(str);
		dlen = slen[0] + 1 + slen[1];
		dst = ft_calloc(dlen + 1, sizeof(char));
		if (dst)
		{
			ft_strlcpy(dst, *rtn, dlen + 1);
			ft_strlcpy(dst + slen[0], " ", dlen + 1);
			ft_strlcpy(dst + slen[0] + 1, str, dlen + 1);
		}
		free(*rtn);
		*rtn = dst;
	}
	return (*rtn);
}

char	*get_wildcard(char *str)
{
	char			*rtn;
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	rtn = NULL;
	dirent = readdir(dir);
	while (dirent)
	{
		if (ft_strncmp(dirent->d_name, ".", 2) != 0
			&& ft_strncmp(dirent->d_name, "..", 3) != 0
			&& _is_match(str, dirent->d_name))
		{
			rtn = _concat(&rtn, dirent->d_name);
			if (rtn == NULL)
				break ;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (rtn);
}
