#ifndef PARSE_TREE_H
# define PARSE_TREE_H

typedef unsigned long size_t;

typedef struct s_parse_tree
{
	unsigned int	type;
	size_t			len;
	char			*string;
	t_parse_tree	*parent;
	t_parse_tree	*left;
	t_parse_tree	*right;
}   t_parse_tree;

int				is_empty(t_parse_tree *node);
int				size(t_parse_tree *node);
t_parse_tree	*root(t_parse_tree *node);
int				is_internal(t_parse_tree *node);
int				is_external(t_parse_tree *node);
int				is_root(t_parse_tree *node);

#endif
