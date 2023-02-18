/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:13:05 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/12 01:07:43 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"
#include "libft.h"
#include "stack.h"

// token -> word, pipe, &&, ||
t_parse_tree	*parse(t_list *lst_token)
{
	t_parse_tree	*root;
	t_stack			*stack;

	root = NULL;
	stack = NULL;
	
}