/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/07 06:45:52 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "prompt.h"
#include "lexer.h"
#include "parse.h"

extern int	executor(const char *command);

static void	run(struct s_minishell *sh, char *command)
{
	t_lex_token		*lst_token;
	t_parse_tree	*tree_parse;

	//	lexing
	lst_token = lexer(command);
	tree_parse = parse(lst_token);
	//	parsing
	//	expansion
	//	redirection

	clear_parse_tree(tree_parse);
	free(tree_parse);
	ft_lstclear((t_list **)&lst_token, free);
	sh->exit_status = executor(command);
}

int	main(void)
{
	static struct s_minishell	sh;
	char						*command;

	env_init(sh.environ, HASH_MAX);
	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		run(&sh, command);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
