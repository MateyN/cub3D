/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:04:38 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/22 16:04:34 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	**ft_add_map(int fd)
{
	char	**map;
	char	*line;
	char	*buff;
	int		ret;

	buff = ft_calloc(2, sizeof(char));
	if (!buff)
		return (NULL);
	line = ft_strdup("");
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buff, 1);
		if (ret == -1)
		{
			free(buff);
			return (NULL);
		}
		if (ret != 0)
			line = ft_strjoin(line, buff);
	}
	map = ft_split(line, '\n');
	free(line);
	return (map);
}

int	main(int ac, char **av)
{
	char	**map;
	t_game	game;
	int		fd;

	(void)ac;
	game.angle = PI / 2;
	fd = open(av[1], O_RDONLY);
	map = ft_add_map(fd);
	ft_cub3d(&game, map);
	return (0);
}
