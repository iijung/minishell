/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:12:10 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/22 06:52:52 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

void	go_heredoc_check_delimiter(
t_env **table,
char *file,
struct s_redirect *redirect_content)
{
	if (file[0] == '\0')
		ft_putendl_fd("heredoc : delimiter not found", 2);
	else
		redirect_content->fd = get_heredoc(table, file);
}

t_redirect	*new_redirect(t_env **table, t_e_lex type, char *file)
{
	t_redirect			*rtn;
	struct s_redirect	*content;

	content = ft_calloc(1, sizeof(struct s_redirect));
	rtn = ft_lstnew(content);
	if (rtn == NULL || content == NULL)
	{
		free(content);
		ft_lstdelone(rtn, NULL);
		return (NULL);
	}
	content->type = type;
	content->filename = file;
	content->fd = -1;
	if (type == LEXEME_HEREDOC)
		go_heredoc_check_delimiter(table, file, content);
	content->flag = O_RDONLY;
	if (type == LEXEME_OUTFILE)
		content->flag = O_CREAT | O_TRUNC | O_WRONLY;
	if (type == LEXEME_ADDFILE)
		content->flag = O_CREAT | O_APPEND | O_WRONLY;
	return (rtn);
}

void	free_redirect(void *param)
{
	struct s_redirect *const	content = param;

	if (content == NULL)
		return ;
	if (content->fd != -1)
		close(content->fd);
	content->fd = -1;
	free(content->filename);
	content->filename = NULL;
	free(content);
}

static int	_open(char *file, int flag)
{
	int		fd;
	int		count;
	t_list	*path;

	path = get_wildcard(file);
	count = ft_lstsize(path);
	fd = -1;
	if (path == NULL)
		fd = open(file, flag, 0666);
	else if (count == 1)
		fd = open(path->content, flag, 0666);
	ft_lstclear(&path, free);
	if (fd != -1)
		return (fd);
	ft_putstr_fd(file, STDERR_FILENO);
	if (count == 1)
		perror(":");
	else
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	return (-1);
}

int	redirect(t_redirect *curr)
{
	int					io;
	struct s_redirect	*content;

	while (curr && curr->content)
	{
		content = curr->content;
		if (content->fd == -1 && content->type != LEXEME_HEREDOC)
		{
			content->fd = _open(content->filename, content->flag);
			if (content->fd == -1)
				return (-1);
		}
		if (content->type == LEXEME_HEREDOC || content->type == LEXEME_INFILE)
			io = STDIN_FILENO;
		else
			io = STDOUT_FILENO;
		if (dup2(content->fd, io) == -1)
			return (-1);
		close(content->fd);
		content->fd = -1;
		curr = curr->next;
	}
	return (0);
}
