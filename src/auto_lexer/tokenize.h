
enum
{
	E_STRING = 1 << 0,
	E_PIPE = 1 << 1,
	E_AND = 1 << 2,
	E_OR = 1 << 3,
	E_SUB_S = 1<< 4,
	E_SUB_E = 1<< 5
};

typedef struct s_token
{
	unsigned int	type;
	char			*string;
}	t_token;
