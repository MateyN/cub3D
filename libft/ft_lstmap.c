#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*res;

	new = 0;
	while (lst)
	{
		res = ft_lstnew(f(lst->content));
		if (!res)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, res);
		lst = lst->next;
	}
	return (new);
}
