/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/17 18:17:10 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "lexer.h"

int	main(void)
{
	char	*command;
	t_list	*tokens;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		tokens = lex(command);
		ft_lstclear(&tokens, free);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
