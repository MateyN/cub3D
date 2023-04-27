/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:14:50 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/27 10:25:23 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
@brief Generates the 3D projection of the walls in the game.
This function uses ray-casting to calculate the distance to the walls and their
height on the projection plane, and then renders them in a 3D perspective.
@param game A pointer to the game struct containing all relevant information.
@return void.
*/

void render_3d_view(t_game *game)
{
    int		i;
    t_wall	wall;

    i = 0;
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

void	render_3d_wall(t_game *game, int i, t_wall wall)
{
	t_img	*wall_texture;

	if (game->rays[i].vert_hit)
	{
		if (game->rays[i].ray_left)
			wall_texture = game->sprites->we;
		else
			wall_texture = game->sprites->ea;
		wall.texture_x = (int)(game->rays[i].hit_y
				* wall_texture->width / TILES) % wall_texture->width;
	}
	else
	{
		if (game->rays[i].ray_up)
			wall_texture = game->sprites->no;
		else
			wall_texture = game->sprites->so;
		wall.texture_x = (int)(game->rays[i].hit_x
				* wall_texture->width / TILES) % wall_texture->width;
	}
	draw_wall(game, wall, wall_texture, i);
}

void	render(t_game *game)
{
	mlx_put_image_to_window(game->mlx,
		game->win, game->image->img, 0, 0);
}