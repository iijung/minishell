/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:47:21 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/18 22:53:50 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H
# include "environ.h"
# include "parse.h"
# include "expand.h"
# include <fcntl.h>

typedef t_list	t_redirect;

struct s_redirect
{
	int		fd;
	t_e_lex	type;
	int		flag;
	char	*filename;
};

extern t_redirect	*new_redirect(t_env **table, t_e_lex type, char *file);
extern void			free_redirect(void *param);
extern int			redirect(t_redirect *curr);
extern void			debug_print_redirection_list(t_redirect *redirect);

#endif
