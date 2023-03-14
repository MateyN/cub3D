/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:04:38 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/14 14:01:20 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_add_map(int fd)
{
	char	**map;
	char	*saver;
	char	*buff;
	int		rb;

	buff = ft_calloc(2, sizeof(char));
	if (!buff)
		return (NULL);
	saver = ft_strdup("");
	rb = 1;
	while (rb != 0)
	{
		rb = read(fd, buff, 1);
		if (rb == -1)
		{
			free(buff);
			return (NULL);
		}
		if (rb != 0)
			saver = ft_strjoin(saver, buff);
	}
	// free(buff);
	map = ft_split(saver, '\n');
	free(saver);
	return (map);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	game.angle = M_PI_2;
	(void)ac;
	fd = open(av[1], O_RDONLY);
	game.map = ft_add_map(fd);
	close(fd);
	ft_game(&game);
	return (0);
}
