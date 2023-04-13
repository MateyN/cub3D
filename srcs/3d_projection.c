/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:12:20 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 11:03:15 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void generate_3d_projection(t_game *game)
{
    int i;
    t_wall wall;

    i = -1;
    while (++i < MAPWIDTH)
    {
        wall.corr_dist = game->rays[i].dist * cos(game->rays[i].angle - game->player->angle);
        game->player->dist_proj_plane = (MAPWIDTH / 2) / tan(FOV / 2);
        wall.wall_height = (TILES / wall.corr_dist) * game->player->dist_proj_plane;
        wall.draw_y = (MAPHEIGHT / 2) - (wall.wall_height / 2);
        if (wall.draw_y < 0)
            wall.draw_y = 0;
        wall.draw_x = (MAPHEIGHT / 2) + (wall.wall_height / 2);
        if (wall.draw_x > MAPHEIGHT)
            wall.draw_x = MAPHEIGHT;
        // Decrease the distance to the projection plane to make walls appear closer
        game->player->dist_proj_plane /= 2;
        render_3d_wall(game, i, wall);
        // Reset the distance to the original value for the next wall
        game->player->dist_proj_plane *= 2;
    }
}
