#include "libft.h"

void	*top(t_list *stack)
{
	return (ft_lstlast(stack)->content);
}