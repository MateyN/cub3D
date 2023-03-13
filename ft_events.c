/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/13 13:06:03 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define FOV 1.04719755 // 60 degree
# define RIGHT 124
# define LEFT 123


void	draw_ray(t_game *game, double angle)
{
	double x = game->xc;
	double y = game->yc;
	int i = 0;
	while (i < 400)
	{
		mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xffffff);
		x += cos(angle);
		y += sin(angle);
		int index_i = y / 25;
		int index_j = x / 25;
		if (game->map[index_i][index_j] == '1')
			break ;
		i++;
	}
}

void ft_move(int i, int x, int y, t_game *game)
{
    int j;

    i = y / 25;
    j = x / 25;
    if (game->map[i][j] == '0')
    {
        game->xc = x;
        game->yc = y;
        fill_map(game);
        draw_pixel(game);
        draw_ray(game, game->angle);
        draw_ray(game, game->angle + (FOV / 2));
        draw_ray(game, game->angle - (FOV / 2));
    }
}

void	rotate_right(t_game *game)
{
	game->angle += 0.3;
    fill_map(game);
	draw_pixel(game);
	draw_ray(game, game->angle);
	draw_ray(game, game->angle + (FOV / 2));
	draw_ray(game, game->angle - (FOV / 2));
}

void	rotate_left(t_game *game)
{
	game->angle -= 0.3;
    fill_map(game);
	draw_pixel(game);
	draw_ray(game, game->angle);
	draw_ray(game, game->angle + (FOV / 2));
	draw_ray(game, game->angle - (FOV / 2));

}

int	ft_events(int keycode, t_game *game)
{
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	if (keycode == 13)
		ft_move(0, game->xc + (10 * cos(game->angle)), game->yc + (10 * sin(game->angle)), game);
	if (keycode == 1)
		ft_move(1, game->xc - (10 * cos(game->angle)), game->yc - (10 * sin(game->angle)), game);
	if (keycode == 2)
		ft_move(2, game->xc + (10 * cos(game->angle)), game->yc, game);
	if (keycode == 0)
		ft_move(3, game->xc - (10 * cos(game->angle)), game->yc, game);
	if (keycode == RIGHT)
		rotate_right(game);
	if (keycode == LEFT)
		rotate_left(game);
	return (0);
}