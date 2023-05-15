/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:51:29 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/05/15 17:05:05 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_syntax_error(t_parse *tree)
{
	if (tree->left && is_syntax_error(tree->left))
		return (1);
	if (tree->right && is_syntax_error(tree->right))
		return (1);
	/*
	current node syntax check
	*/
}