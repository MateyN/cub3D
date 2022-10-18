/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:16:20 by mnikolov          #+#    #+#             */
/*   Updated: 2021/10/27 13:32:05 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)

{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
