/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:07:45 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/23 04:23:08 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <signal.h>
# include <termios.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"

extern char	*prompt(void);
extern void	set_terminal(void);

#endif
