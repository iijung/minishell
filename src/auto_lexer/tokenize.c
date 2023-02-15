#include "../../lib/libft/libft.h"

t_token	*get_next_token(const char *cursor)
{
	t_token	new_token;


}

static void	skip_ifs(const char **string)
{
	while (is_ifs(**string))
		(*string)++;
}

void	tokenize(const char *input)
{
	t_token	*token_lst;
	char	*start;
	int		token_len;

	token_lst = NULL;
	while (*input)
	{
		skip_ifs(&input);
		if (*input == '"')
			read_squote();
	}
}
