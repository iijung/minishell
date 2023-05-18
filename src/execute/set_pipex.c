/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:40:50 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/18 14:45:08 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	debug_print_redirection_list(t_list *redirect)
{
	struct s_redirect_data	*data;

	while (redirect)
	{
		data = redirect->content;
		printf("================\n");
		printf("fd : %d\n", data->fd);
		printf("type : %d\n", data->type);
		printf("filename : %s\n", data->filename);
		redirect = redirect->next;
	}
}

static t_lex_lst	*_redirect(
	t_e_lex type,
	t_lex_lst *curr,
	struct s_pipex *pipex
)
{
	t_list					*lst_redirect;
	struct s_redirect_data	*redirect_data;

	if (curr == NULL)
		return (NULL);
	curr = skip_lexeme_ifs(curr->next);
	lst_redirect = ft_calloc(sizeof(t_list), 1);
	redirect_data = ft_calloc(sizeof(struct s_redirect_data), 1);
	lst_redirect->content = redirect_data;
	redirect_data->type = type;
	redirect_data->filename = read_string_sequence(&curr);
	ft_lstadd_back(&pipex->redirect, lst_redirect);
	return (curr);
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
	char				*tmp[2];
	t_list *const		argl = ft_lstnew(NULL);

	if (lexeme_type(curr->content) == LEXEME_DQUOTE)
	{
		argl->content = ft_strdup("");
		curr = curr->next;
		while (curr)
		{
			if (lexeme_type(curr->content) == LEXEME_DQUOTE)
				break ;
			tmp[0] = lexeme_str(curr->content);
			ft_assert(tmp[0] == NULL, __FILE__, __LINE__);
			tmp[1] = ft_strjoin(argl->content, tmp[0]);
			ft_assert(tmp[1] == NULL, __FILE__, __LINE__);
			free(tmp[0]);
			free(argl->content);
			argl->content = tmp[1];
			curr = curr->next;
		}
	}
	else
		argl->content = lexeme_str(curr->content);
	ft_lstadd_back(&pipex->argl, argl);
	return (curr->next);
}

static void	_last(struct s_pipex *pipex)
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
}

void	set_pipex(t_lex_lst *curr, struct s_pipex *pipex)
{
	char	*tmp;

	while (curr)
	{
		if (is_redirection_lex(curr->content))
			curr = _redirect(lexeme_type(curr->content), curr, pipex);
		else if (lexeme_type(curr->content) == LEXEME_ENVIRONMENT)
			curr = _environ(curr, pipex);
		else if (lexeme_type(curr->content) == LEXEME_WILDCARD)
		{
			tmp = lexeme_str(curr->content);
			ft_lstadd_back(&pipex->argl, get_wildcard(tmp));
			free(tmp);
			curr = curr->next;
		}
		else if (lexeme_type(curr->content) == LEXEME_DQUOTE
			|| lexeme_type(curr->content) == LEXEME_STRING)
			curr = _arg(curr, pipex);
		else
			curr = skip_lexeme_ifs(curr);
	}
	_last(pipex);
	debug_print_redirection_list(pipex->redirect);
}
