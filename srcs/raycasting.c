/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:34:03 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/17 11:09:59 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_intersection	*draw_horz(t_game *game, double angle, int i)
{
	t_intersection	*h;

	h = (t_intersection *)malloc(sizeof(t_intersection));
	h->wall_hit = 0;
	h->hit_x = 0;
	h->hit_y = 0;
	h->touch_y = floor(game->player->y / TILES) * TILES;
	if (game->rays[i].ray_down)
		h->touch_y += TILES;
	h->touch_x = game->player->x
		+ (h->touch_y - game->player->y) / tan(angle);
	h->step_y = TILES;
	if (game->rays[i].ray_up)
		h->step_y *= -1;
	h->step_x = TILES / tan(angle);
	if (game->rays[i].ray_left && h->step_x > 0)
		h->step_x *= -1;
	if (game->rays[i].ray_right && h->step_x < 0)
		h->step_x *= -1;
	find_hor_wall_hit(game, h, i);
	return (h);
}

t_intersection	*draw_vert(t_game *game, double angle, int i)
{
	t_intersection	*v;

	v = (t_intersection *)malloc(sizeof(t_intersection));
	v->wall_hit = 0;
	v->hit_x = 0;
	v->hit_y = 0;
	v->touch_x = floor(game->player->x / TILES) * TILES;
	if (game->rays[i].ray_right)
		v->touch_x += TILES;
	v->touch_y = game->player->y
		+ (v->touch_x - game->player->x) * tan(angle);
	v->step_x = TILES;
	if (game->rays[i].ray_left)
		v->step_x *= -1;
	v->step_y = TILES * tan(angle);
	if (game->rays[i].ray_up && v->step_y > 0)
		v->step_y *= -1;
	if (game->rays[i].ray_down && v->step_y < 0)
		v->step_y *= -1;
	find_vert_wall_hit(game, v, i);
	return (v);
}

void	fill_ray(t_ray *ray, t_intersection *dir, int boolean)
{
	ray->hit_x = dir->hit_x;
	ray->hit_y = dir->hit_y;
	ray->vert_hit = boolean;
	ray->dist = dir->hit_dist;
}

void	draw_ray(t_game *game, double angle, int i)
{
	t_intersection	*h;
	t_intersection	*v;

	game->rays[i].ray_down = (angle > 0 && angle < PI);
	game->rays[i].ray_up = !game->rays[i].ray_down;
	game->rays[i].ray_right = (angle < 0.5 * PI
			|| angle > 1.5 * PI);
	game->rays[i].ray_left = !game->rays[i].ray_right;
	h = draw_horz(game, angle, i);
	v = draw_vert(game, angle, i);
	h->hit_dist = get_dist_to_wall(game, h);
	v->hit_dist = get_dist_to_wall(game, v);
	if (v->hit_dist < h->hit_dist)
		fill_ray(&game->rays[i], v, 1);
	else
		fill_ray(&game->rays[i], h, 0);
	if (game->rays[i].dist == 0)
		game->rays[i].dist = 0.0001;
	game->rays[i].angle = angle;
	free(h);
	free(v);
}

void	draw_rays(t_game *game)
{
	int		i;
	float	angle;

	i = -1;
	while (++i < MAPWIDTH)
	{
		angle = game->player->angle
			+ tan((i - MAPWIDTH / 2) / game->player->dist_proj_plane);
		draw_ray(game, angle, i);
	}
}
