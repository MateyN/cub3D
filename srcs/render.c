/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:14:50 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/09 11:33:01 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	render_3d_view(t_game *game)
{
	int		i;
	t_wall	wall;

	i = -1;
	while (++i < MAPWIDTH)
	{
		wall.corr_dist = game->rays[i].dist * \
			cos(game->rays[i].angle - game->player->angle);
		game->player->dist_proj_plane = (MAPWIDTH / 2) / tan(FOV / 2);
		wall.wall_height = (TILES / wall.corr_dist) * \
			game->player->dist_proj_plane;
		wall.draw_y = (MAPHEIGHT / 2) - (wall.wall_height / 2);
		if (wall.draw_y < 0)
			wall.draw_y = 0;
		wall.draw_x = (MAPHEIGHT / 2) + (wall.wall_height / 2);
		if (wall.draw_x > MAPHEIGHT)
			wall.draw_x = MAPHEIGHT;
		game->player->dist_proj_plane /= 2;
		render_3d_wall(game, i, wall);
		game->player->dist_proj_plane *= 2;
	}
}

/**
 * calculates the texture coordinate for the point of intersection
 * by scaling the x or y-coordinate of the intersection by the texture width,
 * and then taking the remainder of that value when divided by the tile size
 * to make sure that we draw the texture 
 * as many times as necessary to cover the whole wall
*/
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
