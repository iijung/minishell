#include "parse.h"

void	clear_parse_tree(t_parse *root, void (*f)(void *))
{
	t_parse	*left_tree;
	t_parse	*right_tree;

	left_tree = root->left;
	right_tree = root->right;
	if (left_tree)
	{
		clear_parse_tree(left_tree, f);
		free(left_tree);
	}
	if (right_tree)
	{
		clear_parse_tree(right_tree, f);
		free(right_tree);
	}
	ft_lstclear(&root->node, f);
	if (root->node)
		free(root->node);
}

void	debug_print_parse_tree(t_parse *parse_tree)
{
	printf("debug\n");
	if (parse_tree->is_subshell)
		printf("this is SUBSHELL_NODE\n");
	if (parse_tree->node)
		ft_lstiter(parse_tree->node, debug);
	if (parse_tree->left)
		debug_print_parse_tree(parse_tree->left);
	if (parse_tree->right)
		debug_print_parse_tree(parse_tree->right);
}

t_lex_lst	*get_type_node(t_lex_lst *token_lst, t_e_lex type)
{
	int		dquote_flag;
	int		subshell_depth;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	subshell_depth = 0;
	while (token_lst)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
				subshell_depth++;
			else if (lex_data->type == LEXEME_PARENTHESIS_CLOSE)
				subshell_depth--;
			else if (subshell_depth == 0 && lex_data->type == type)
				return (token_lst);
		}
		token_lst = token_lst->next;
	}
	return (NULL);
}

t_lex_lst	*get_root_node(t_lex_lst **token_lst)
{
	t_lex_lst	*root_node;

	root_node = get_type_node(*token_lst, LEXEME_AND);
	if (root_node)
		return (root_node);
	root_node = get_type_node(*token_lst, LEXEME_OR);
	if (root_node)
		return (root_node);
	root_node = get_type_node(*token_lst, LEXEME_PIPE);
	if (root_node)
		return (root_node);
	return (NULL);
}

t_parse	*make_new_node(t_lex_lst *token_lst)
{
	t_parse	*root;

	if (token_lst == NULL)
		return (NULL);
	root = ft_calloc(1, sizeof(t_parse));
	root->node = token_lst;
	return (root);
}

int	has_subshell(t_lex_lst *token_lst)
{
	int			dquote_flag;
	t_s_lex		*lex_data;

	dquote_flag = 0;
	while (token_lst)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0)
		{
			if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
				return (1);
		}
		token_lst = token_lst->next;
	}
	return (0);
}

t_lex_lst	*get_before_first_subshell_open(\
t_lex_lst *token_lst, t_lex_lst **first_open)
{
	int		dquote_flag;
	t_s_lex	*lex_data;

	dquote_flag = 0;
	lex_data = token_lst->content;
	if (lex_data->type == LEXEME_PARENTHESIS_OPEN)
	{
		*first_open = token_lst;
		return (NULL);
	}
	while (token_lst->next)
	{
		lex_data = token_lst->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_OPEN)
		{
			*first_open = token_lst->next;
			return (token_lst);
		}
		token_lst = token_lst->next;
	}
	return (NULL);
}

t_lex_lst	*get_before_last_subshell_close(t_lex_lst *token_lst)
{
	int			dquote_flag;
	t_s_lex		*lex_data;
	t_lex_lst	*last_before_close;

	dquote_flag = 0;
	while (token_lst->next)
	{
		lex_data = token_lst->next->content;
		if (lex_data->type == LEXEME_DQUOTE)
			dquote_flag ^= 1;
		else if (dquote_flag == 0 && lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			last_before_close = token_lst;
		token_lst = token_lst->next;
	}
	return (last_before_close);
}

t_lex_lst	*make_new_token_lst(t_lex_lst *start, t_lex_lst *end)
{
	t_lex_lst	*new_token_lst;

	new_token_lst = NULL;
	if (start == NULL || end == NULL)
		return (NULL);
	while (start != end)
	{
		ft_lstadd_back(&new_token_lst, ft_lstnew(start->content));
		start = start->next;
	}
	ft_lstadd_back(&new_token_lst, ft_lstnew(start->content));
	return (new_token_lst);
}

void	split_by_subshell(\
t_lex_lst *token_lst, t_parse **left, t_parse **right, t_lex_lst **mid)
{
	t_lex_lst	*before_first_subshell_open;
	t_lex_lst	*first_subshell_open;
	t_lex_lst	*before_last_subshell_close;
	t_lex_lst	*tmp_token1;
	t_lex_lst	*tmp_token2;
	
	before_first_subshell_open = \
			get_before_first_subshell_open(token_lst, &first_subshell_open);
	before_last_subshell_close = get_before_last_subshell_close(token_lst);
	if (before_first_subshell_open)
		before_first_subshell_open->next = NULL;
	tmp_token1 = first_subshell_open->next;
	ft_lstdelone(first_subshell_open, free);
	tmp_token2 = before_last_subshell_close->next;
	before_last_subshell_close->next = NULL;
	*left = make_new_node(tmp_token1);
	if (before_first_subshell_open)
		*mid = token_lst;
	tmp_token1 = tmp_token2;
	tmp_token2 = tmp_token2->next;
	ft_lstdelone(tmp_token1, free);
	*right = make_new_node(tmp_token2);
}

t_parse	*subshell_parsing(t_parse *root, t_lex_lst *token_lst)
{
	t_parse	*prev_root;

	root->is_subshell = 1;
	split_by_subshell(token_lst, &root->left, &root->right, &root->node);
	prev_root = root->left;
	// printf("BEFORE SUBSHELL INNER PARSING!!\n");
	// ft_lstiter(root->left->node, debug);
	// printf("\n\n");
	root->left = parse(root->left->node);
	free(prev_root);
	return (root);
}

t_lex_lst	*get_left_start(t_lex_lst *start, t_lex_lst *root)
{
	t_lex_lst	*left_start;

	left_start = start;
	while (start->next)
	{
		if (start->next == root)
		{
			start->next = NULL;
			return (left_start);
		}
		start = start->next;
	}
	return (left_start);
}

t_lex_lst	*get_right_start(t_lex_lst *root)
{
	t_lex_lst	*right_start;

	right_start = root->next;
	root->next = NULL;
	return (right_start);
}

static void	loop_check_match(\
t_list *token, int *dquote_flag, int *parenthesis_dep)
{
	t_s_lex	*cur_token_data;

	while (token)
	{
		cur_token_data = token->content;
		if (cur_token_data->type == LEXEME_DQUOTE)
			*dquote_flag ^= 1;
		else if ((cur_token_data->type == LEXEME_PARENTHESIS_OPEN || \
				cur_token_data->type == LEXEME_PARENTHESIS_CLOSE) && \
				*dquote_flag == 0)
		{
			if (cur_token_data->type == LEXEME_PARENTHESIS_OPEN)
				(*parenthesis_dep)++;
			else
				(*parenthesis_dep)--;
		}
		token = token->next;
	}
}

int	check_quote_parenthesis_match_error(t_list *token)
{
	int	dquote_flag;
	int	parenthesis_dep;

	dquote_flag = 0;
	parenthesis_dep = 0;
	loop_check_match(token, &dquote_flag, &parenthesis_dep);
	if (dquote_flag == 0 && parenthesis_dep == 0)
		return (0);
	else
		return (1);
}

int	check_empty_subshell(t_lex_lst *lexlst)
{
	t_s_lex	*front_lex_data;
	t_s_lex	*rear_lex_data;

	while (lexlst && lexlst->next)
	{
		rear_lex_data = lexlst->content;
		front_lex_data = lexlst->next->content;
		if (rear_lex_data->type == LEXEME_PARENTHESIS_OPEN
			&& front_lex_data->type == LEXEME_PARENTHESIS_CLOSE)
			return (1);
		lexlst = lexlst->next;
	}
	return (0);
}

static int	is_about_string_token(t_lex_lst *token)
{
	const t_s_lex	*lex_data = token->content;

	return (lex_data->type == LEXEME_STRING
		|| lex_data->type == LEXEME_ENVIRONMENT
		|| lex_data->type == LEXEME_WILDCARD
		|| lex_data->type == LEXEME_DQUOTE);
}

static int	is_ifs_token(t_lex_lst *token)
{
	const t_s_lex	*lex_data = token->content;

	return (lex_data->type == LEXEME_IFS);
}

void	delete_useless_ifs(t_lex_lst *token_lst)
{
	t_lex_lst	*rear;
	t_lex_lst	*front;
	t_lex_lst	*mid;
	t_lex_lst	*to_delete;

	if (ft_lstsize(token_lst) < 3)
		return ;
	rear = token_lst;
	mid = rear->next;
	front = mid->next;
	while (front)
	{
		if (!is_about_string_token(mid) && is_ifs_token(front))
		{
			mid->next = front->next;
			to_delete = front;
			ft_lstdelone(to_delete, free);
			front = front->next;
			continue ;
		}
		else if (is_ifs_token(mid) && !is_about_string_token(front))
		{
			to_delete = mid;
			rear->next = front;
			ft_lstdelone(to_delete, free);
			mid = front;
			front = front->next;
			continue ;
		}
		front = front->next;
		mid = mid->next;
		rear = rear->next;
	}
}

t_parse	*parse(t_lex_lst *token_lst)
{
	t_parse	*root;
	t_lex_lst	*operator;

	if (check_quote_parenthesis_match_error(token_lst))
		return (NULL);
	else if (check_empty_subshell(token_lst))
		return (NULL);
	delete_useless_ifs(token_lst);
	operator = get_root_node(&token_lst);
	if (operator == NULL)
	{
		if (has_subshell(token_lst))
		{
			root = ft_calloc(1, sizeof(t_parse));
			return (subshell_parsing(root, token_lst));
		}
		return (make_new_node(token_lst));
	}
	else
	{
		root = ft_calloc(1, sizeof(t_parse));
		root->node = operator;
		root->left = parse(get_left_start(token_lst, root->node));
		root->right = parse(get_right_start(root->node));
	}
	return (root);
}
