/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:52:07 by mnikolov          #+#    #+#             */
/*   Updated: 2021/11/04 16:28:19 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lenght(int nbr)

{
	int	num_len;

	num_len = 0;
	if (nbr < 0)
		num_len++;
	while (nbr)
	{
		nbr = nbr / 10;
		num_len++;
	}
	return (num_len);
}

char	*ft_digit(int n, int num_len, char *str)

{
	int	num;

	num = 0;
	while (n != 0)
	{
		num_len--;
		num = n % 10;
		str[num_len] = num + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)

{
	char	*str;
	int		num_len;

	num_len = ft_lenght(n);
	str = (char *)ft_calloc(num_len + 1, 1);
	if (!str)
		return (NULL);
	if (n == 0)
		*str = n / 10 + '0';
	else if (n <= 0)
	{
		if (n == -2147483648)
		{
			ft_strlcpy(str, "-2147483648", num_len + 1);
			return (str);
		}
		*str = '-';
		n = n * -1;
	}
	str = ft_digit(n, num_len, str);
	return (str);
}
