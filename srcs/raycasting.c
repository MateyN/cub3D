/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:34:03 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/27 10:23:51 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_intersection	*draw_horz(t_game *game, double angle, int i)
{
	t_intersection	*h;

	h = (t_intersection *)malloc(sizeof(t_intersection));
	h->wall_hit = 0;
	h->wall_interX = 0;
	h->wall_interY = 0;
	// finds the y-coordinate of the nearest horizontal grid line below the player's position
	h->currentY = floor(game->player->y / TILES) * TILES;
	if (game->rays[i].ray_down)
		h->currentY += TILES;
	h->currentX = game->player->x
		+ (h->currentY - game->player->y) / tan(angle);
	h->deltaY = TILES;
	if (game->rays[i].ray_up)
		h->deltaY *= -1;
	h->deltaX = TILES / tan(angle);
	// Check if the ray is pointing at the correct direction
	if (game->rays[i].ray_left && h->deltaX > 0)
		h->deltaX *= -1; // adjust direction if necessary
	if (game->rays[i].ray_right && h->deltaX < 0)
		h->deltaX *= -1;
	dda_hor_step(game, h, i);
	return (h);
}

t_intersection	*draw_vert(t_game *game, double angle, int i)
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

void	draw_ray(t_game *game, double angle, int i)
{
	t_intersection	*h;
	t_intersection	*v;

	game->rays[i].ray_down = (angle > 0 && angle < PI);
	game->rays[i].ray_up = !game->rays[i].ray_down;
	// radians = degrees * (PI / 180)
	game->rays[i].ray_right = (angle < ANGLE_90 || angle > ANGLE_270); // 90 degrees * (PI / 180) = 1.5708 (1.5) radians
			// 30 degrees * (PI / 180) = 0.5236 (0.5) radians
	game->rays[i].ray_left = !game->rays[i].ray_right;
	h = draw_horz(game, angle, i);
	v = draw_vert(game, angle, i);
	//printf("Horz intersection at %p\n", h);
    //printf("Vert intersection at %p\n", v);
	h->hit_dist = get_dist_to_wall(game, h);
	v->hit_dist = get_dist_to_wall(game, v);
	if (v->hit_dist < h->hit_dist)
		fill_ray(&game->rays[i], v, 1);
	else
		fill_ray(&game->rays[i], h, 0);
		//printf("Filled ray at %p\n", &game->rays[i]);
	if (game->rays[i].dist == 0)
		game->rays[i].dist = 0.0001;
	game->rays[i].angle = angle;
	//printf("Freeing horz intersection at %p\n", h);
    //printf("Freeing vert intersection at %p\n", v);
	free(h);
	free(v);
}

void	draw_rays(t_game *game)
{
	int		i;
	float	angle;
	
	i = 0;
	//printf("Counter start at %d\n", i);
	while (i < MAPWIDTH)
	{
		//printf("Counter is at %d\n", i);
		angle = game->player->angle
			+ tan((i - MAPWIDTH / 2) / game->player->dist_proj_plane);
		draw_ray(game, angle, i);
		i++;
	}
	//printf("Counter finish at %d\n", i);
}
