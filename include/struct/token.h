/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:13:19 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/03 02:21:18 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	char			*string;
	unsigned int	type;
	// linkedlist
	struct s_token	*prev;
	struct s_token	*next;
	// binary tree
	struct s_token	*parent;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;


#endif
