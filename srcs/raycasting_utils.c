/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:34 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 13:57:36 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calc_wall_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

double	get_dist_to_wall(t_game *game, t_cast *dir)
{
	if (dir->wall_hit)
		return (calc_wall_dist(game->player->x, game->player->y,
				dir->hit_x, dir->hit_y));
	else
		return (INT_MAX);
}

void	find_hor_wall_hit(t_game *game, t_cast *h, int i)
{
	while (h->touch_x >= 0
		&& h->touch_x <= game->map->map_size_x
		&& h->touch_y >= 0
		&& h->touch_y <= game->map->map_size_y)
	{
		if (!can_move(game->map, h->touch_x,
				h->touch_y - (game->rays[i].ray_up == TRUE)))
		{
			h->wall_hit = TRUE;
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

void	find_vert_wall_hit(t_game *game, t_cast *v, int i)
{
	while (v->touch_x >= 0
		&& v->touch_x <= game->map->map_size_x
		&& v->touch_y >= 0
		&& v->touch_y <= game->map->map_size_y)
	{
		if (!can_move(game->map,
				v->touch_x - (game->rays[i].ray_left == TRUE),
				v->touch_y))
		{
			v->wall_hit = TRUE;
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
