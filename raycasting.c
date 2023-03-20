/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:06:05 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 12:35:34 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_ray(t_game *game, double angle)
{
    double x;
    double y;

    x = game->xc;
    y = game->yc;
    while (1)
    {
        my_mlx_pixel_put(game, (int)x, (int)y, 0xFFFF00);
        x += cos(angle) * 2;
        y += sin(angle) * 2;
        if (game->map[(int)(y / MAPHEIGHT)][(int)(x / MAPWIDTH)] == '1')
            break;
    }
}

void    draw_rays(t_game *game)
{
    double fov;
    double distperray;
    //double ray_angle;
    //int i;

    //i = 0;
    //ray_angle = game->angle - (fov / 2);
    fov = FOV;
    distperray = fov / (MAPWIDTH * game->map_size_x);
    //while (i < MAPWIDTH)
    while (fov / 2 > 0)
    {
        //ray_angle = atan2(i - MAPWIDTH / 2, MAPWIDTH / 2 / tan(fov / 2));
        //draw_ray(game, ray_angle);
        //i++;
        draw_ray(game, game->angle + (fov / 2));
        draw_ray(game, game->angle - (fov / 2));
        fov -= distperray;
    }
}