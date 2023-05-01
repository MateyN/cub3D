/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:34:13 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/01 12:23:27 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
@brief Calculates the distance between two points (x1,y1) and (x2,y2)
@param x1: X-coordinate of first point
@param y1: Y-coordinate of first point
@param x2: X-coordinate of second point
@param y2: Y-coordinate of second point
@return The calculated distance between the two points
*/

int	calc_wall_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

/**
@brief Calculates the distance from the player's position to the intersection point with a wall
@param game: A pointer to the game struct
@param inter: A pointer to the intersection struct
@return The calculated distance to the wall if it was hit, otherwise the maximum integer value
*/

int	get_dist_to_wall(t_game *game, t_intersection *inter)
{
	if (inter->wall_hit)
		return (calc_wall_dist(game->player->x, game->player->y,
				inter->wall_interX, inter->wall_interY));
	else
		return (INT_MAX);
}
/**
@brief implements the DDA algorithm for horizontal lines.
It starts from the current position (h->currentX, h->currentY)
and moves in the direction (h->deltaX, h->deltaY) until it hits a wall.
If it hits a wall, it sets the wall_hit flag to 1 and records the
intersection point (h->wall_interX, h->wall_interY).
@param game: a pointer to the game struct.
@param h: The intersection structure for the horizontal ray.
@param i: The index of the current ray in the rays array.
@return void.
*/
void	dda_hor_step(t_game *game, t_intersection *h, int i)
{
	while (h->currentX >= 0
		&& h->currentX <= game->map->map_size_x
		&& h->currentY >= 0
		&& h->currentY <= game->map->map_size_y)
	{
		if (!can_move(game->map, h->currentX,
				h->currentY - (game->rays[i].ray_up == 1)))
		{
			h->wall_hit = 1;
			h->wall_interX = h->currentX;
			h->wall_interY = h->currentY;
			break ;
		}
		else
		{
			h->currentX += h->deltaX;
			h->currentY += h->deltaY;
		}
	}
}
/**
@brief implements the DDA algorithm for vertical lines.
It starts from the current position (v->currentX, v->currentY)
and moves in the direction (v->deltaX, v->deltaY) until it hits a wall.
If it hits a wall, it sets the wall_hit flag to 1 and store the
intersection point (v->wall_interX, v->wall_interY).
@params 
*game a pointer to the game struct.
*v The intersection structure for the vertical ray.
*i The index of the current ray in the rays array.
@return void.
*/ 

void	dda_vert_step(t_game *game, t_intersection *v, int i)
{
	while (v->currentX >= 0
		&& v->currentX <= game->map->map_size_x
		&& v->currentY >= 0
		&& v->currentY <= game->map->map_size_y)
	{
		if (!can_move(game->map,
				v->currentX - (game->rays[i].ray_left == 1),
				v->currentY))
		{
			v->wall_hit = 1;
			v->wall_interX = v->currentX;
			v->wall_interY = v->currentY;
			break ;
		}
		else
		{
			v->currentX += v->deltaX;
			v->currentY += v->deltaY;
		}
	}
}
