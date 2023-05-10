/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:46 by krioja            #+#    #+#             */
/*   Updated: 2023/05/04 12:45:27 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	file_checker(char *str, char *extension)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		exit_error("Error: No extension found", str);
	else if (ft_strncmp(ext, extension, 5))
		exit_error("Error: Invalid file extension", ext);
}

void	file_parsing(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (line_parsing(game, line))
			{
				map_parsing(game, line, fd);
				return ;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parsing(t_game *game, char *str)
{
	int		fd;

	file_checker(str, ".cub\0");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_strerr(str, 2);
	init_game(game);
	file_parsing(game, fd);
	close(fd);
	check_map_content(game, game->map->map);
	check_map(game);
	check_map_borders(game->map->map);
}
