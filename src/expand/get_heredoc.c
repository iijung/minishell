/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 00:14:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/06 01:02:37 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"

enum e_pipe_direction
{
	PIPE_OUT,
	PIPE_IN
};

static char	*_env_next(t_env **table, char *line, int fd)
{
	size_t	len;
	char	*key;
	char	*val;

	len = 0;
	while (line[len] && (ft_isalpha(line[len]) || line[len] == '_'))
		++len;
	key = ft_strndup(line, len);
	if (key == NULL)
		return (NULL);
	val = env_get_val(table, key);
	free(key);
	if (val && write(fd, val, ft_strlen(val)) < 0)
		return (NULL);
	return (line + len);
}

static int	_expand(int fd, char *line, t_env **table)
{
	char	*left;
	char	*right;

	left = line;
	while (left && left[0])
	{
		right = ft_strchr(left, '$');
		if (right == NULL)
		{
			if (write(fd, left, ft_strlen(left)) < 0)
				return (-1);
			return (0);
		}
		if (right - left > 0 && write(fd, left, right - left) < 0)
			return (-1);
		left = _env_next(table, right + 1, fd);
	}
	return (-1);
}

int	get_heredoc(t_env **table, char *word)
{
	int		pipes[2];
	size_t	word_len;
	char	*line;

	if (word == NULL || pipe(pipes) == -1)
		return (-1);
	word_len = ft_strlen(word);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, word, word_len) == 0
			&& (line[word_len] == '\n' || line[word_len] == '\0'))
			break ;
		if (_expand(pipes[PIPE_IN], line, table) < 0)
		{
			close(pipes[PIPE_OUT]);
			pipes[PIPE_OUT] = -1;
			break ;
		}
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipes[PIPE_IN]);
	return (pipes[PIPE_OUT]);
}
