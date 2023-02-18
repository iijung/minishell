#include "libft.h"

void	*pop(t_list *stack)
{
	t_list	*to_return;

	to_return = ft_lstlast(stack->content);
	free(ft_lstlast(stack));
	return (to_return);
}