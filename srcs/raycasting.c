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

#include "../includes/cub3d.h"

t_intersection	*draw_horz(t_game *game, float angle, int i)
{
	t_intersection	*h;

	h = (t_intersection *)malloc(sizeof(t_intersection));
	h->wall_hit = 0;
	h->wall_inter_x = 0;
	h->wall_inter_y = 0;
	h->current_y = floor(game->player->y / TILES) * TILES;
	if (game->rays[i].ray_down)
		h->current_y += TILES;
	h->current_x = game->player->x
		+ (h->current_y - game->player->y) / tan(angle);
	h->delta_y = TILES;
	if (game->rays[i].ray_up)
		h->delta_y *= -1;
	h->delta_x = TILES / tan(angle);
	if (game->rays[i].ray_left && h->delta_x > 0)
		h->delta_x *= -1;
	if (game->rays[i].ray_right && h->delta_x < 0)
		h->delta_x *= -1;
	dda_hor_step(game, h, i);
	return (h);
}

t_intersection	*draw_vert(t_game *game, float angle, int i)
{
	t_intersection	*v;

	v = (t_intersection *)malloc(sizeof(t_intersection));
	v->wall_hit = 0;
	v->wall_inter_x = 0;
	v->wall_inter_y = 0;
	v->current_x = floor(game->player->x / TILES) * TILES;
	if (game->rays[i].ray_right)
		v->current_x += TILES;
	v->current_y = game->player->y
		+ (v->current_x - game->player->x) * tan(angle);
	v->delta_x = TILES;
	if (game->rays[i].ray_left)
		v->delta_x *= -1;
	v->delta_y = TILES * tan(angle);
	if (game->rays[i].ray_up && v->delta_y > 0)
		v->delta_y *= -1;
	if (game->rays[i].ray_down && v->delta_y < 0)
		v->delta_y *= -1;
	dda_vert_step(game, v, i);
	return (v);
}

void	fill_ray(t_ray *ray, t_intersection *dir, int boolean)
{
	ray->hit_x = dir->wall_inter_x;
	ray->hit_y = dir->wall_inter_y;
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
	game->rays[i].ray_down = (angle > 0 && angle < PI);
	game->rays[i].ray_up = !game->rays[i].ray_down;
	game->rays[i].ray_right = (angle < ANGLE_90 || angle > ANGLE_270);
	game->rays[i].ray_left = !game->rays[i].ray_right;
	h = draw_horz(game, angle, i);
	v = draw_vert(game, angle, i);
	h->hit_dist = get_dist_to_wall(game, h);
	v->hit_dist = get_dist_to_wall(game, v);
	if (v->hit_dist < h->hit_dist)
		fill_ray(&game->rays[i], v, 1);
	else
		fill_ray(&game->rays[i], h, 0);
	game->rays[i].angle = angle;
	free(h);
	free(v);
}

/**
@brief loops through the columns of the screen,
calculates the angle of the ray for each column based on the player's position
and the distance to the projection plane,
and calls the draw_ray() function to cast the ray 
and determine the distance to the nearest wall in that direction
114 - calculate the angle at which to cast each ray
*/
void	draw_rays(t_game *game)
{
	int		i;
	float	angle;

	i = 0;
	while (i < MAPWIDTH)
	{
		angle = game->player->angle
			+ atan((i - MAPWIDTH / 2) / game->player->dist_proj_plane);
		draw_ray(game, angle, i);
		i++;
	}
}
