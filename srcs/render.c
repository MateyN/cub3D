/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:14:50 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/18 13:27:39 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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