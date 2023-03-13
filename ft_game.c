/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:04:20 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/13 12:23:48 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 25, i * 25);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window (game->mlx, game->win, game->floor, j * 25, i * 25);
			j++;
		}
		i++;
	}
}

void	read_img(t_game *game)
{
	int	width;
	int	height;

	game->floor = mlx_xpm_file_to_image(game->mlx, "./assets/white.xpm", &width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, "./assets/square.xpm", &width, &height);
}

void draw_triangle(t_game *game, int x, int y)
{
    mlx_pixel_put(game->mlx, game->win, game->xc + x, game->yc + y, 0xFFFF00);
    mlx_pixel_put(game->mlx, game->win, game->xc - x, game->yc + y, 0xFFFF00);
    mlx_pixel_put(game->mlx, game->win, game->xc + y, game->yc - x, 0xFFFF00);
}

void draw_pixel(t_game *game)
{
    int radius;
    int x;
    int y;
    int decision;
    
    radius = 3; // radius of the circle
    x = 0; // x-coordinate of the current pixel being drown
    y = radius; // y-coordinate of the current pixel being drown
    decision = 3 - (2 * radius); // decision parameter for Bresenham's algorithm

    // draw the first point at the top of the triangle
    draw_triangle(game, x, y);

    // loop through all the pixels in the circle until x is greater than y
    while (y >= x)
    {
        x++; // increment x

        // check if the decision parameter is greater than zero
        // if it is, decrement y and update the decision parameter
        if (decision > 0)
        {
            y--;
            decision += 4 * (x - y) + 10;
        }
        // if the decision parameter is not greater than zero, update it using the simpler formula
        else
            decision += 4 * x + 6;

        // draw the pixel at the current x,y coordinates
        draw_triangle(game, x, y);
    }
}

void	ft_game(t_game *game)
{
	game->map_size_y = 0;
	while (game->map[game->map_size_y])
		game->map_size_y++;
	game->map_size_x = ft_strlen(game->map[0]);
	game->xc = (game->map_size_x * 25) / 2 - 20;
	game->yc = (game->map_size_y * 25) / 2 - 10;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_size_x * 25, game->map_size_y * 25, "Cub3D");
	read_img(game);
	fill_map(game);
	draw_pixel(game);
	mlx_key_hook(game->win, ft_events, game);
	mlx_loop(game->mlx);
}
