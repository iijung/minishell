/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 02:07:45 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/06 02:42:07 by minjungk         ###   ########.fr       */
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

#endif
