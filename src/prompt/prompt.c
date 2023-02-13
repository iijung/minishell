/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:10:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/13 22:16:05 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*prompt(void)
{
	char	*line;
	char	*command;

	line = readline("minishell$ : ");
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	command = ft_strtrim(line, " ");
	if (command == NULL || *command == '\0')
	{
		free(command);
		return (NULL);
	}
	add_history(command);
	free(line);
	return (command);
}
