/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:34:03 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/09 11:26:59 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_intersection	*draw_horz(t_game *game, float angle, int i)
{
	t_intersection	*h;

	h = (t_intersection *)malloc(sizeof(t_intersection));
	h->wall_hit = 0;
	h->wall_interX = 0;
	h->wall_interY = 0;
	// finds the y-coordinate of the nearest horizontal grid line below the player's position
	h->currentY = floor(game->player->y / TILES) * TILES;
	// if the ray is pointing downwards, we add the tile height to the current y-coordinate
	if (game->rays[i].ray_down)
		h->currentY += TILES;
	// calculate the x-coordinate of the intersection point to find the horizontal distance
	// from the player to the nearest vertical grid line (y = mx + c) <- equation of a straight line
	h->currentX = game->player->x
		+ (h->currentY - game->player->y) / tan(angle);
	h->deltaY = TILES;
	if (game->rays[i].ray_up)
		h->deltaY *= -1;
	h->deltaX = TILES / tan(angle); // distance between two consecutive vertical grid lines that the ray intersects with
	// check if the ray is pointing at the correct direction
	if (game->rays[i].ray_left && h->deltaX > 0)
		h->deltaX *= -1; // adjust direction if necessary
	if (game->rays[i].ray_right && h->deltaX < 0)
		h->deltaX *= -1;\
	// we use the DDA algorithm to step through the grid until an intersection with a wall is found
	dda_hor_step(game, h, i);
	return (h);
}

t_intersection	*draw_vert(t_game *game, float angle, int i)
{
	t_intersection	*v;

	v = (t_intersection *)malloc(sizeof(t_intersection));
	v->wall_hit = 0;
	v->wall_interX = 0;
	v->wall_interY = 0;
	v->currentX = floor(game->player->x / TILES) * TILES;
	if (game->rays[i].ray_right)
		v->currentX += TILES;
	v->currentY = game->player->y
		+ (v->currentX - game->player->x) * tan(angle);
	v->deltaX = TILES;
	if (game->rays[i].ray_left)
		v->deltaX *= -1;
	v->deltaY = TILES * tan(angle);
	if (game->rays[i].ray_up && v->deltaY > 0)
		v->deltaY *= -1;
	if (game->rays[i].ray_down && v->deltaY < 0)
		v->deltaY *= -1;
	dda_vert_step(game, v, i);
	return (v);
}

void	fill_ray(t_ray *ray, t_intersection *dir, int boolean)
{
	ray->hit_x = dir->wall_interX;
	ray->hit_y = dir->wall_interY;
	ray->vert_hit = boolean;
	ray->dist = dir->hit_dist;
}

void	draw_ray(t_game *game, float angle, int i)
{
	t_intersection	*h;
	t_intersection	*v;
	
	angle = fmod(angle, (2 * PI));
  	if (angle < 0)
    angle += (2 * PI);
	 // determine which direction the ray is facing
	game->rays[i].ray_down = (angle > 0 && angle < PI);// facing down if the angle is between 0 and 180 degrees
	game->rays[i].ray_up = !game->rays[i].ray_down; // if not it is facing up
	// radians = degrees * (PI / 180)
	// facing right if angle is between 0-90 degrees or 270-360 degrees
	game->rays[i].ray_right = (angle < ANGLE_90 || angle > ANGLE_270); // 90 degrees * (PI / 180) = 1.5708 (1.5) radians
			// 30 degrees * (PI / 180) = 0.5236 (0.5) radians
	game->rays[i].ray_left = !game->rays[i].ray_right; // if not it is facing left
	h = draw_horz(game, angle, i);
	v = draw_vert(game, angle, i);
	// calculate the distance from the player to the wall at each horizontal and vertical intersections points
	h->hit_dist = get_dist_to_wall(game, h);
	v->hit_dist = get_dist_to_wall(game, v);
	// calculate which one is closer to the player and fill it
	if (v->hit_dist < h->hit_dist)
		fill_ray(&game->rays[i], v, 1);
	else
		fill_ray(&game->rays[i], h, 0);
	//if (game->rays[i].dist == 0)
	//	game->rays[i].dist = 0.01;
	game->rays[i].angle = angle;
	free(h);
	free(v);
}
/**
@brief loops through the columns of the screen,
calculates the angle of the ray for each column based on the player's position
and the distance to the projection plane,
and calls the draw_ray() function to cast the ray and determine the distance to the nearest wall in that direction
*/
void	draw_rays(t_game *game)
{
	int		i;
	float	angle;
	
	i = 0;
	while (i < MAPWIDTH)
	{
		angle = game->player->angle
			+ atan((i - MAPWIDTH / 2) / game->player->dist_proj_plane); // calculate the angle at which to cast each ray
		draw_ray(game, angle, i);
		i++;
	}
}
