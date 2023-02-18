#include "libft.h"

void	*push(t_list *stack, void *content)
{
	t_list	*new_lstnode;

	new_lstnode = ft_lstnew(content);
	ft_lstadd_back(&stack, new_lstnode);
	return (new_lstnode);
}