/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:26 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 10:43:58 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	get_width(char *line)
{
	int	len;

	len = ft_strlen(line);
	return (len * TILES);
}

int	can_move(t_map *map, float x, float y)
{
	int	x2;
	int	y2;

	x2 = floor(x / TILES);
	y2 = floor(y / TILES);
	if (y < 0 || y > map->map_size_y)
		return (FALSE);
	if (x < 0 || x > get_width(map->map[y2]))
		return (FALSE);
	if (map->map[y2][x2] != '1')
		return (TRUE);
	return (FALSE);
}

void	move_player(t_game *game)
{
	float	step_x;
	float	step_y;
	float	forward;
    float   side;

	step_x = 0;
	step_y = 0;
	game->player->angle += game->player->rotdir * game->player->rotspeed;
	forward = game->player->move * game->player->movespeed;
    side = game->player->side * (game->player->movespeed - 2);
	step_x += (cos(game->player->angle) * forward);
	step_x += (cos(game->player->angle + M_PI / 2) * side);
    step_y += (sin(game->player->angle) * forward);
    step_y += (sin(game->player->angle + M_PI / 2) * side);
	step_x *= 5;
	step_y *= 5;
	if (can_move(game->map, game->player->x + step_x, game->player->y))
		game->player->x += step_x / 5;
	if (can_move(game->map, game->player->x, game->player->y + step_y))
		game->player->y += step_y / 5;
}
