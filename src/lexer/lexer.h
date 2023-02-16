#include "libft.h"

enum
{
	E_STRING = 1 << 0,
	E_DQUOTE = 1 << 1,
	E_SQUOTE = 1 << 2,
	E_PIPE = 1 << 3,
	E_AND = 1 << 4,
	E_OR = 1 << 5,
	E_SUB_S = 1 << 6,
	E_SUB_E = 1 << 7,
	E_ERROR = 1 << 8
};

typedef struct s_lex_token
{
	char				*string;
	struct s_lex_token	*next;
	unsigned int		type;
}	t_lex_token;

t_lex_token	*lexer(const char *input);