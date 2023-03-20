/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:06:54 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 12:54:33 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_player(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i <= 1)
    {
        j = 0;
        while (j <= 1)
        {
            my_mlx_pixel_put(game, game->xc + j, game->yc + i, 0xFFFF00);
            my_mlx_pixel_put(game, game->xc - j, game->yc + i, 0xFFFF00);
            my_mlx_pixel_put(game, game->xc + j, game->yc - i, 0xFFFF00);
            my_mlx_pixel_put(game, game->xc - j, game->yc - i, 0xFFFF00);
            j++;
        }
        i++;
    }
}


void	draw_floor(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_size_y * MAPHEIGHT)
	{
		x = 0;
		while (x < game->map_size_x * MAPWIDTH)
		{
            my_mlx_pixel_put(game, (int)x, (int)y, 0x90EE90);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_game *game)
{
	int	i;
	int	j;

	draw_floor(game);
    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
                my_mlx_put_image_to_window(game, j * MAPWIDTH, i * MAPHEIGHT, 0xA52A2A);
                j++;
        }
        i++;
    }
}