#include "libft.h"

typedef t_list t_stack;

void	*push(t_list *stack, void *content);
void	*pop(t_list *stack);
void	*top(t_list *stack);
size_t	size(t_list *stack);
