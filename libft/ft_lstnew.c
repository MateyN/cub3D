/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:13:45 by mnikolov          #+#    #+#             */
/*   Updated: 2022/03/24 18:55:33 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
