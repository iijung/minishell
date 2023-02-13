/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/13 22:14:36 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "sigsetting.h"
#include "lexer.h"

int	main(void)
{
	char	*command;

	setting_terminal(MINISHELL_NO_CHILD);
	setting_signal(MINISHELL_NO_CHILD);
	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		lex(command);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
