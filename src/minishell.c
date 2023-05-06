/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/06 20:05:48 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "prompt.h"
#include "lexer.h"
#include "parse.h"
#include "executor.h"

extern int	executor(t_env **table, const char *command);

static int	run(t_env **table, char *command)
{
	t_list	*tokens;
	// t_pipex	*pipex;
	t_parse	*parse_tree;

	tokens = lex(command);
	//	parsing
	parse_tree = parse(tokens);
	if (parse_tree == 0)
	{
		printf("syntax error\n");
		ft_lstclear(&tokens, free);
		return (1);
	}
	else
	{
		printf("!!\n");
		debug_print_parse_tree(parse_tree);
		clear_parse_tree(parse_tree);
	}
	free(parse_tree);
	//	expansion
	//	redirection
	// pipex = new_pipex(table, command);
	// return (execute(pipex));
	(void)table;
	return (1);
}

int	main(void)
{
	char	*command;
	t_env	**table;

	table = env_load();
	ft_assert(table == NULL, __FILE__, __LINE__);
	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		run(table, command);
		free(command);
	}
	env_clear(&table);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
