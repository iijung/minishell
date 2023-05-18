/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:55:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/18 22:25:00 by minjungk         ###   ########.fr       */
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

static void	_concat(t_list **rtn, char *str)
{
	t_list	*lst;

	lst = ft_lstnew(NULL);
	while (lst)
	{
		lst->content = ft_strdup(str);
		if (lst->content == NULL)
			break ;
		ft_lstadd_back(rtn, lst);
		return ;
	}
	ft_lstclear(rtn, free);
}

t_list	*get_wildcard(char *str)
{
	t_list			*rtn;
	DIR				*dir;
	struct dirent	*dirent;

	if (str == NULL || ft_strchr(str, '*') == NULL)
		return (NULL);
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
			_concat(&rtn, dirent->d_name);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (rtn);
}
