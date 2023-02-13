/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:55:19 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/13 22:19:25 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	setting_terminal(int option)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (option == MINISHELL_HAS_CHILD || option == MINISHELL_HEREDOC || \
			option == MINISHELL_NO_CHILD)
	{
		term.c_lflag &= ~ECHOCTL;
	}
	else if (option == EXE_CHILD)
	{
		term.c_lflag |= ECHOCTL;
	}
	tcsetattr(0, TCSANOW, &term);
}
