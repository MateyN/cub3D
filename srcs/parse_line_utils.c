/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:17 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/26 15:38:02 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_direction(char dir)
{
	if (dir == 'N' || dir == 'S' || dir == 'W' || dir == 'E')
		return (1);
	return (0);
}

int	set_map(t_game *game)
{
    if (game->map->floor == -1 || game->map->ceiling == -1
            || game->map->no == NULL || game->map->so == NULL
            || game->map->we == NULL || game->map->ea == NULL)
		exit_str("Error: Texture missing");
	return (0);
}

void	check_length(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ',');
	if (!split)
		exit_str("Error");
	while (split[i])
		i++;
	if (i != 3)
		exit_error("Error: Invalid color", line);
	ft_free_ptr(split);
}
