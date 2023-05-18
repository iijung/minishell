/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:49:28 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/18 13:35:38 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "environ.h"
# include "builtin.h"
# include "parse.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef t_list	t_pipex;

struct s_redirect_data
{
	int		fd;
	int		type;
	char	*filename;
};

struct s_pipex
{
	t_list		*argl;
	t_list		*redirect;
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
		int		is_heredoc;
		char	*heredoc_word;
		int		in_fd;
		int		out_fd;
		char	*infile;
		char	*outfile;
		int		outflag;
	};
};

extern t_list		*get_wildcard(char *str);
extern int			get_heredoc(t_env **table, char *word);

extern void			redirect(struct s_pipex *content);
extern t_pipex		*new_pipex(t_env **table, t_parse *tree);
extern void			set_pipex(t_lex_lst *curr, struct s_pipex *pipex);
extern int			run_pipex(t_pipex *pipex);
extern int			all_pipex(t_pipex *pipex);
extern void			free_pipex(void *param);

extern int			execute(t_env **table, t_parse *tree);
char	*read_string_sequence(t_lex_lst **curr);

#endif
