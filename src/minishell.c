/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 11:48:47 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"
#include "prompt.h"
#include "lexer.h"
#include "parse.h"
#include "executor.h"

static int	run(t_env **table, char *command)
{
	int			exit_status;
	t_lex_lst	*tokens;
	t_parse		*parse_tree;

	exit_status = SYNTAX_ERROR_EXIT_STATUS;
	tokens = lex(command);
	if (tokens)
	{
		parse_tree = parse(tokens);
		if (parse_tree == NULL || is_syntax_error(parse_tree))
			ft_putstr_fd("minishell: syntax error\n", 2);
		else
			exit_status = execute(table, parse_tree);
		clear_parse_tree(parse_tree, free);
		if (parse_tree == NULL)
			ft_lstclear(&tokens, free);
	}
	return (exit_status);
}

int	main(void)
{
	char	*command;
	t_env	**table;
	char	*str_exit_status;

	table = env_load();
	ft_assert(table == NULL, __FILE__, __LINE__);
	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		str_exit_status = ft_itoa(run(table, command));
		env_set(table, "?", str_exit_status);
		free(str_exit_status);
		free(command);
	}
	env_clear(&table);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
