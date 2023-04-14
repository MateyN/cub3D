/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:26 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/14 11:07:10 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_width(char *line)
{
	int	lenght;

	lenght = ft_strlen(line);
	return (lenght * TILES);
}

int	can_move(t_map *map, double x, double y)
{
	int	x2;
	int	y2;

	x2 = floor(x / TILES);
	y2 = floor(y / TILES);
	if (y < 0 || y > map->map_size_y)
		return (0);
	if (x < 0 || x > get_width(map->map[y2]))
		return (0);
	if (map->map[y2][x2] != '1')
		return (1);
	return (0);
}

void	move_player(t_game *game)
{
	int	step_x;
	int	step_y;
	int	forward;
    int sideways;

	step_x = 0;
	step_y = 0;
	game->player->angle += game->player->rotdir * game->player->rotspeed;
	forward = game->player->move * game->player->movespeed;
    sideways = game->player->side * (game->player->movespeed - 2);	
	step_x = step_x + (cos(game->player->angle) * forward);
	step_x = step_x + (cos(game->player->angle + PI / 2) * sideways);
    step_y = step_y + (sin(game->player->angle) * forward);
    step_y = step_y + (sin(game->player->angle + PI / 2) * sideways);
	step_x = step_x * 5;
	step_y = step_y * 5;
	if (can_move(game->map, game->player->x + step_x, game->player->y))
		game->player->x += step_x / 5; // movespeed
	if (can_move(game->map, game->player->x, game->player->y + step_y))
		game->player->y += step_y / 5; // movespeed
}
