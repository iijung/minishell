/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:40:50 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/15 04:55:52 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_lex_lst	*_redirect(
	t_e_lex type,
	t_lex_lst *curr,
	struct s_pipex *pipex
)
{
	curr = skip_lexeme_ifs(curr);
	if (type == LEXEME_HEREDOC || type == LEXEME_INFILE)
	{
		free(pipex->infile);
		pipex->infile = lexeme_str(curr->content);
		pipex->is_heredoc = (type == LEXEME_HEREDOC);
	}
	else if (type == LEXEME_OUTFILE || type == LEXEME_ADDFILE)
	{
		free(pipex->outfile);
		pipex->outfile = lexeme_str(curr->content);
		if (type == LEXEME_OUTFILE)
			pipex->outflag = O_CREAT | O_TRUNC | O_WRONLY;
		else
			pipex->outflag = O_CREAT | O_APPEND | O_WRONLY;
	}
	return (curr->next);
}

static t_lex_lst	*_environ(t_lex_lst *curr, struct s_pipex *pipex)
{
	int			i;
	char		*key;
	char		*val;
	char		**sp;
	t_list		*arg;

	key = lexeme_str(curr->content);
	ft_assert(key == NULL, __FILE__, __LINE__);
	val = env_get_val(pipex->envp, key);
	free(key);
	if (val == NULL)
		sp = ft_split("", ' ');
	else
		sp = ft_split(val, ' ');
	ft_assert(sp == NULL, __FILE__, __LINE__);
	i = 0;
	while (sp[i])
	{
		arg = ft_lstnew(sp[i]);
		ft_assert(arg == NULL, __FILE__, __LINE__);
		ft_lstadd_back(&pipex->argl, arg);
		++i;
	}
	free(sp);
	return (curr->next);
}

t_lex_lst	*_arg(t_lex_lst *curr, struct s_pipex *pipex)
{
	char				*tmp;
	t_list *const		argl = ft_lstnew(NULL);

	if (lexeme_type(curr->content) == LEXEME_DQUOTE)
	{
		argl->content = ft_strdup("");
		curr = curr->next;
		while (curr)
		{
			if (lexeme_type(curr->content) == LEXEME_DQUOTE)
				break ;
			tmp = ft_strjoin(argl->content, curr->content);
			ft_assert(tmp == NULL, __FILE__, __LINE__);
			free(argl->content);
			argl->content = tmp;
			curr = curr->next;
		}
	}
	else
		argl->content = lexeme_str(curr->content);
	ft_lstadd_back(&pipex->argl, argl);
	return (curr->next);
}

static t_lex_lst	*_last(t_lex_lst *curr, struct s_pipex *pipex)
{
	int		i;
	t_list	*argp;

	pipex->argc = ft_lstsize(pipex->argl);
	pipex->argv = ft_calloc(pipex->argc + 1, sizeof(char *));
	ft_assert(pipex->argv == NULL, __FILE__, __LINE__);
	i = 0;
	argp = pipex->argl;
	while (argp)
	{
		pipex->argv[i++] = argp->content;
		argp = argp->next;
	}
	if (pipex->is_heredoc)
		pipex->in_fd = get_heredoc(pipex->envp, pipex->infile);
	return (curr);
}

t_lex_lst	*set_pipex(t_lex_lst *curr, struct s_pipex *pipex)
{
	while (curr)
	{
		if (lexeme_type(curr->content) == LEXEME_PIPE)
			return (_last(curr->next, pipex));
		else if (lexeme_type(curr->content) == LEXEME_HEREDOC
			|| lexeme_type(curr->content) == LEXEME_INFILE
			|| lexeme_type(curr->content) == LEXEME_ADDFILE
			|| lexeme_type(curr->content) == LEXEME_OUTFILE)
			curr = _redirect(lexeme_type(curr->content), \
					skip_lexeme_ifs(curr->next), pipex);
		else if (lexeme_type(curr->content) == LEXEME_ENVIRONMENT)
			curr = _environ(curr, pipex);
		else if (lexeme_type(curr->content) == LEXEME_WILDCARD)
		{
			ft_lstadd_back(&pipex->argl, get_wildcard(curr->content));
			curr = curr->next;
		}
		else if (lexeme_type(curr->content) == LEXEME_STRING)
			curr = _arg(curr, pipex);
		else
			curr = skip_lexeme_ifs(curr->next);
	}
	return (_last(curr, pipex));
}
