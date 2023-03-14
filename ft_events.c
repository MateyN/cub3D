/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/14 12:58:34 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_game *game, double angle)
{
	double x = game->xc;
	double y = game->yc;
	int i = 0;
	while (i < 400)
	{
		mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFFFF00);
		x += cos(angle) * 3;
		y += sin(angle) * 3;
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
        double angle = game->angle - (FOV / 2);
        for (int i = 0; i < 400; i++)
        {
            draw_ray(game, angle);
            angle += FOV / 400;
        }
    }
}

void	rotate_right(t_game *game)
{
	game->angle += 0.3;
    fill_map(game);
	draw_pixel(game);
    double angle = game->angle - (FOV / 2);
    for (int i = 0; i < 400; i++)
    {
        draw_ray(game, angle);
        angle += FOV / 400;
    }
}

void	rotate_left(t_game *game)
{
	game->angle -= 0.3;
    fill_map(game);
	draw_pixel(game);
    double angle = game->angle - (FOV / 2);
    for (int i = 0; i < 400; i++)
    {
        draw_ray(game, angle);
        angle += FOV / 400;
    }

}

int	ft_events(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_W)
		ft_move(0, game->xc + (10 * cos(game->angle)), game->yc + (10 * sin(game->angle)), game);
	if (keycode == KEY_S)
		ft_move(1, game->xc - (10 * cos(game->angle)), game->yc - (10 * sin(game->angle)), game);
	if (keycode == KEY_D)
		ft_move(2, game->xc + (10 * cos(game->angle)), game->yc, game);
	if (keycode == 0)
		ft_move(3, game->xc - (10 * cos(game->angle)), game->yc, game);
	if (keycode == RIGHT)
		rotate_right(game);
	if (keycode == LEFT)
		rotate_left(game);
	return (0);
}