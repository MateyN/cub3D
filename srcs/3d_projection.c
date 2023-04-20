/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:12:20 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/20 10:16:40 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**
@brief Generates the 3D projection of the walls in the game.
This function uses ray-casting to calculate the distance to the walls and their
height on the projection plane, and then renders them in a 3D perspective.
@param game A pointer to the game struct containing all relevant information.
@return void.
*/

void generate_3d_projection(t_game *game)
{
    int		i;
    t_wall	wall;

    i = -1;
    while (++i < MAPWIDTH)
    {
        // Calculate the corrected distance to the wall using ray-casting and player angle
        wall.corr_dist = game->rays[i].dist * cos(game->rays[i].angle - game->player->angle);
        // Calculate the distance to the projection plane based on FOV and screen width
        game->player->dist_proj_plane = (MAPWIDTH / 2) / tan(FOV / 2);
        // Calculate the height of the wall on the projection plane
        wall.wall_height = (TILES / wall.corr_dist) * game->player->dist_proj_plane;
        // Calculate the Y-coordinate at which to start drawing the wall
        wall.draw_y = (MAPHEIGHT / 2) - (wall.wall_height / 2);	
        if (wall.draw_y < 0)
            wall.draw_y = 0;
        // Calculate the X-coordinate at which to stop drawing the wall
        wall.draw_x = (MAPHEIGHT / 2) + (wall.wall_height / 2);	
        if (wall.draw_x > MAPHEIGHT)
            wall.draw_x = MAPHEIGHT;
        // Decrease the distance to the projection plane to make walls appear closer
        game->player->dist_proj_plane /= 2;
        // Render the wall in 3D perspective
        render_3d_wall(game, i, wall);
        // Reset the distance to the projection plane to the original value for the next wall
        game->player->dist_proj_plane *= 2;	
    }
}