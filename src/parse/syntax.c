/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:51:29 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/21 16:04:10 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
/*
all func in this file,
return 1 at syntax error ditected
*/
int	is_syntax_error(t_parse *root)
{
	t_lex_lst	*lex_lst;
	t_s_lex		*lex_data;

	if (root->is_subshell)
	{
		if (root->node)
			return (1);
		return (0);
	}
	else
	{
		if (root->right && is_syntax_error(root->right))
			return (1);
		lex_lst = root->node;
		lex_data = lex_lst->content;
		if (is_operator_lex(lex_data))
			return (root->left == 0 || root->right == 0);
	}
	if (root->left && is_syntax_error(root->left))
		return (1);
	return (0);
}
