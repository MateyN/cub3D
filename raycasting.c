/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:06:05 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 11:42:00 by mnikolov         ###   ########.fr       */
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
        x += cos(angle) * 3;
        y += sin(angle) * 3;
        if (game->map[(int)(y / MAPHEIGHT)][(int)(x / MAPWIDTH)] == '1')
            break;
    }
}

void    draw_rays(t_game *game)
{
    double fov;
    double distperray;

    fov = FOV;
    distperray = fov / (MAPWIDTH * game->map_size_x);
    while (fov / 2 > 0)
    {
        draw_ray(game, game->angle + (fov / 2));
        draw_ray(game, game->angle - (fov / 2));
        fov -= distperray;
    }
}