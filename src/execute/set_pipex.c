/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:40:50 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 02:18:50 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static t_lex_lst	*_redirect(
	t_e_lex type,
	t_lex_lst *curr,
	struct s_pipex *pipex
)
{
	t_redirect			*tmp;
	char				*file;

	if (curr == NULL)
		return (NULL);
	curr = skip_lexeme_ifs(curr->next);
	if (curr == NULL)
		return (NULL);
	file = NULL;
	curr = combine_string(pipex->envp, curr, &file);
	if (file == NULL)
		return (NULL);
	tmp = new_redirect(pipex->envp, type, file);
	if (tmp == NULL)
	{
		free(file);
		return (NULL);
	}
	ft_lstadd_back(&pipex->redirect, tmp);
	return (curr);
}

static t_lex_lst	*_environ(t_lex_lst *curr, struct s_pipex *pipex)
{
	int			i;
	char		*key;
	char		*val;
	char		**sp;
	t_list		*arg;

	key = lexeme_str(curr);
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
	char	*str;
	t_list	*argl;

	str = NULL;
	curr = combine_string(pipex->envp, curr, &str);
	argl = ft_lstnew(str);
	ft_assert(argl == NULL || str == NULL, __FILE__, __LINE__);
	ft_lstadd_back(&pipex->argl, argl);
	return (curr);
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
}

void	set_pipex(t_lex_lst *curr, struct s_pipex *pipex)
{
	char	*tmp;

	while (curr)
	{
		if (is_redirection_lex(curr->content))
			curr = _redirect(lexeme_type(curr), curr, pipex);
		else if (lexeme_type(curr) == LEXEME_ENVIRONMENT)
			curr = _environ(curr, pipex);
		else if (lexeme_type(curr) == LEXEME_WILDCARD)
		{
			tmp = lexeme_str(curr);
			ft_lstadd_back(&pipex->argl, get_wildcard(tmp));
			free(tmp);
			curr = curr->next;
		}
		else if (lexeme_type(curr) == LEXEME_DQUOTE
			|| lexeme_type(curr) == LEXEME_STRING)
			curr = _arg(curr, pipex);
		else
			curr = skip_lexeme_ifs(curr);
	}
	_last(pipex);
	debug_print_redirection_list(pipex->redirect);
}
