/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:20:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/07 05:01:50 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "prompt.h"
#include "lexer.h"
#include "parse.h"

int	main(void)
{
	char			*command;
	t_lex_token		*lst_token;
	t_parse_tree	*tree_parse;

	while (1)
	{
		command = prompt();
		if (command == NULL)
			continue ;
		lst_token = lexer(command);
		tree_parse = parse(lst_token);

		clear_parse_tree(tree_parse);
		free(tree_parse);
		ft_lstclear((t_list **)&lst_token, free);
		free(command);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
