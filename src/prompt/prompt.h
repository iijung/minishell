/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:07:45 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/20 23:08:59 by minjungk         ###   ########.fr       */
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

#endif
