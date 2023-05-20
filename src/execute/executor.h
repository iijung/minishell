/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:49:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/20 23:22:48 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "environ.h"
# include "builtin.h"
# include "parse.h"
# include "expand.h"
# include "redirect.h"

typedef t_list	t_pipex;

struct s_pipex
{
	t_list		*argl;
	t_redirect	*redirect;
	struct
	{
		pid_t	pid;
		int		argc;
		char	**argv;
		t_env	**envp;
		int		exit_status;
	};
};

extern t_pipex		*new_pipex(t_env **table, t_parse *tree);
extern void			set_pipex(t_lex_lst *curr, struct s_pipex *pipex);
extern int			all_pipex(t_pipex *pipex);
extern void			free_pipex(void *param);

extern int			execute(t_env **table, t_parse *tree);
extern char			*read_string_sequence(t_lex_lst **curr);

#endif
