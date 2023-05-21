/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 00:14:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 13:29:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"
#include <signal.h>
#include <sys/wait.h>

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
	if (line[0] == '?')
		len = 1;
	if (len == 0)
	{
		if (write(fd, "$", 1) < 0)
			return (NULL);
		return (line);
	}
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

static int	_read(t_env **table, char *word, int fd)
{
	const size_t	word_len = ft_strlen(word);
	char			*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, word, word_len) == 0
			&& (line[word_len] == '\n' || line[word_len] == '\0'))
			break ;
		if (_expand(fd, line, table) < 0)
		{
			close(fd);
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (EXIT_SUCCESS);
}

int	get_heredoc(t_env **table, char *word)
{
	pid_t	pid;
	int		status;
	int		pipes[2];

	if (word == NULL || pipe(pipes) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(pipes[PIPE_OUT]);
		exit(_read(table, word, pipes[PIPE_IN]));
	}
	else
	{
		close(pipes[PIPE_IN]);
		status = waitpid_ignore_signal(pid);
		if (status != EXIT_SUCCESS)
		{
			close(pipes[PIPE_OUT]);
			return (-1);
		}
	}
	return (pipes[PIPE_OUT]);
}
