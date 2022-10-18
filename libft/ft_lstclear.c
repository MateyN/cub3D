#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))

{
	t_list	*nxt;

	if (lst)
	{
		while (*lst)
		{
			nxt = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = nxt;
		}
	}
	*lst = NULL;
}
