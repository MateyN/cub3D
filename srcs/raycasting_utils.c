/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:34:13 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/14 12:11:06 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	calc_wall_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

int	get_dist_to_wall(t_game *game, t_intersection *dir)
{
	if (dir->wall_hit)
		return (calc_wall_dist(game->player->x, game->player->y,
				dir->hit_x, dir->hit_y));
	else
		return (INT_MAX);
}

void	find_hor_wall_hit(t_game *game, t_intersection *h, int i)
{
	while (h->touch_x >= 0
		&& h->touch_x <= game->map->map_size_x
		&& h->touch_y >= 0
		&& h->touch_y <= game->map->map_size_y)
	{
		if (!can_move(game->map, h->touch_x,
				h->touch_y - (game->rays[i].ray_up == 1)))
		{
			h->wall_hit = 1;
			h->hit_x = h->touch_x;
			h->hit_y = h->touch_y;
			break ;
		}
		else
		{
			h->touch_x += h->step_x;
			h->touch_y += h->step_y;
		}
	}
}

void	find_vert_wall_hit(t_game *game, t_intersection *v, int i)
{
	while (v->touch_x >= 0
		&& v->touch_x <= game->map->map_size_x
		&& v->touch_y >= 0
		&& v->touch_y <= game->map->map_size_y)
	{
		if (!can_move(game->map,
				v->touch_x - (game->rays[i].ray_left == 1),
				v->touch_y))
		{
			v->wall_hit = 1;
			v->hit_x = v->touch_x;
			v->hit_y = v->touch_y;
			break ;
		}
		else
		{
			v->touch_x += v->step_x;
			v->touch_y += v->step_y;
		}
	}
}
