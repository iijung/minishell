/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:49:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/06 01:14:37 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "environ.h"
# include "builtin.h"
# include "fcntl.h"

typedef t_list	t_pipex;

struct s_pipex
{
	char	*command;
	struct
	{
		pid_t	pid;
		int		argc;
		char	**argv;
		t_env	**envp;
		int		exit_status;
	};
	struct
	{
		int		in_fd;
		int		out_fd;
		char	*infile;
		char	*outfile;
		int		outflag;
	};
};

extern int		get_heredoc(t_env **table, char *word);
extern int		run_pipex(t_pipex *pipex);
extern t_pipex	*new_pipex(t_env **envp, char *command);
extern void		free_pipex(void *param);

extern int		execute(t_pipex *pipex);

#endif
