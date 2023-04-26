/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:04 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/26 14:13:00 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_map(t_game *game)
{
	if (!game->map->no || !game->map->so || !game->map->we || !game->map->ea)
		set_map(game);
	else if (game->map->floor == -1 || game->map->ceiling == -1)
		exit_str("Error: Color missing");
	else if (!game->map->map[0])
		exit_str("Error: Map missing");
	else if (game->player->x == -1 || game->player->y == -1)
		exit_str("Error: Player missing");
}

void	check_map_borders(char **map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (map[0][j] == ' ')
		j++;
	while (map[0][j] == '1')
		j++;
	if (map[0][j] != '1' && map[0][j] != '\0' && map[0][j] != ' ')
		exit_str("Error: Invalid map");
	while (map[i])
	{
		if (map[i][0] == '\0' || map[i][0] == '\t'
			|| map[i][0] == '\n')
			exit_str("Error: Invalid map");
		i++;
	}
}

void	check_map_content(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[++i] && set_map(game) == 0)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || player_direction(map[i][j]))
			{
				if (j > (int)ft_strlen(map[i + 1])
					|| j > (int)ft_strlen(map[i - 1]))
					exit_str("Error: Invalid map");
					// Checks if any of the surrounding elements are not walls or empty spaces
				if (map[i][j - 1] == ' ' || map[i][j - 1] == '\0'
					|| map[i][j + 1] == ' ' || map[i][j + 1] == '\0'
					|| map[i - 1][j] == ' ' || map[i - 1][j] == '\0'
					|| map[i + 1][j] == ' ' || map[i + 1][j] == '\0')
					exit_error("Error: Invalid map", map[i]);
			}
			// Checks if there is a player's starting position if so draw the player
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				draw_player(game, map, i, j);
		}
	}
}

/**
@brief Parses the map by reading from a file descriptor.
@param game A pointer to the game struct.
@param line The current line of the file being read.
@param fd The file descriptor of the map file.
*/
void	map_parsing(t_game *game, char *line, int fd)
{
	char	*tmp;

	while (line)
	{
		if (!is_map(line))
			exit_error("Error: Invalid map", line);
		game->map->height++;
		tmp = ft_strtrim(line, "\n");
		if (game->map->width < (int)ft_strlen(tmp))
			game->map->width = ft_strlen(tmp);
		game->map->map = add_map(game->map->map, tmp);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	game->map->map_size_x = game->map->width * TILES;
	game->map->map_size_y = game->map->height * TILES;
	free(line);
}
