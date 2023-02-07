/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/07 23:25:34 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"

extern void	run(const char *command);

int	main(void)
{
	char	*command;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		run(command);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
