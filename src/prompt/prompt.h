/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:07:45 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/13 22:15:51 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <signal.h>
# include <termios.h>
# include <stdio.h>
# include "readline.h"
# include "history.h"
# include "libft.h"

extern char	*prompt(void);
void	    setting_terminal(int option);

#endif
