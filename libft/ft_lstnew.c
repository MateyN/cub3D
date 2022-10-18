#include "libft.h"

t_list	*ft_lstnew(void *content)

{
	t_list	*new_e;

	new_e = (t_list *)malloc(sizeof(t_list));
	if (!new_e)
		return (NULL);
	new_e->content = content;
	new_e->next = NULL;
		return (new_e);
}

