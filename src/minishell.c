/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/13 00:06:45 by minjungk         ###   ########.fr       */
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
	int			exit_status;
	t_lex_lst	*tokens;
	t_parse		*parse_tree;

	(void)table;
	exit_status = EXIT_FAILURE;
	tokens = lex(command);
	if (tokens)
	{
		parse_tree = parse(tokens);
		if (parse_tree)
		{
			debug_print_parse_tree(parse_tree);
			// exit_status = execute(table, parse_tree);
			clear_parse_tree(parse_tree, free);
		}
		else
		{
			printf("syntax error\n");
			ft_lstclear(&tokens, free);
		}
	}
	return (exit_status);
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
