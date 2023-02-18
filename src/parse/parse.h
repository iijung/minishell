/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:03:18 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/12 01:07:13 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "libft.h"

enum type_parse_node
{
	ROOT,
	APL,
	OPL,
	PL,
	WL,
	W,
	RED
}

enum type_token
{
	WORD,
	AND,
	OR,
	RED_READ,
	RED_HERECOD,
	RED_WRITE,
	RED_APPEND
}

typedef struct s_parse_node
{
	unsigned int	type;
	char			*value;
}	t_parse_node;

typedef struct s_stack
{
	int		cursor;
	int		capacity;
	t_list	*arr_data;
}	t_stack;

typedef struct s_wordline
{
	int		count_outred;
	t_list	*outred;
	int		count_inred;
	t_list	*inred;
	int		count_cmd;
	char 	**cmd;
}	t_wordline;

typedef struct s_parse_tree
{
	t_parse_node		node;
	struct s_parse_tree	*parent;
	struct s_parse_tree	*left;
	struct s_parse_tree	*right;
	t_wordline			*wl;
}	t_parse_tree;

#endif


struct s_content
{
	int			type;
	size_t		len;
	const char	*data;
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;