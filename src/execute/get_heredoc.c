/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 00:14:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/05 16:19:19 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

enum e_pipe_direction
{
	PIPE_OUT,
	PIPE_IN
};

int	get_heredoc(char *word)
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
		if (write(pipes[PIPE_IN], line, ft_strlen(line)) < 0)
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
