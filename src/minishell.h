/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/02/13 22:17:54 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

enum
{
    MINISHELL_NO_CHILD = 1 << 0,
    MINISHELL_HAS_CHILD = 1 << 1,
    MINISHELL_HEREDOC = 1 << 2,
    EXE_CHILD = 1 << 3,
    HEREDOC = 1 << 4
};

#endif
