/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/15 11:56:57 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray(t_game *game, double angle)
{
    double x = game->xc;
    double y = game->yc;

    while (1)
    {
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFFFFFF);
        x += cos(angle) * 2;
        y += sin(angle) * 2;
        int index_i = y / 25;
        int index_j = x / 25;
        if (game->map[index_i][index_j] == '1')
            break ;
    }
}

void ft_move(int i, int x, int y, t_game *game)
{
    double fov = FOV;
    double distperray = fov / (25 * game->map_size_x); // calculate the angular distance between each ray that is cast from the player's position.
	(void)i;
    if (game->map[(y + 3) / 25][(x + 3) / 25] == '1'
        || game->map[(y - 3) / 25][(x - 3) / 25] == '1')
        return ;
    game->xc = x;
    game->yc = y;
    fill_map(game);
    draw_pixel(game);
    draw_ray(game, game->angle);
    while (fov / 2 > 0)
    {
        draw_ray(game, game->angle + (fov / 2));
        draw_ray(game, game->angle - (fov / 2));
        fov -= distperray;
    }
}

void rotate_right(t_game *game)
{
    game->angle += (PI / 180) * 18; // rotate by 18 degrees
    fill_map(game);
    draw_pixel(game);
    double angle = game->angle - (FOV / 2);
    for (int i = 0; i < 400; i++)
    {
        draw_ray(game, angle);
        angle += FOV / 400;
    }
}

void rotate_left(t_game *game)
{
    game->angle -= (PI / 180) * 18; // rotate by 18 degrees
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
	if (keycode == KEY_A)
		ft_move(3, game->xc - (10 * cos(game->angle)), game->yc, game);
	if (keycode == RIGHT)
		rotate_right(game);
	if (keycode == LEFT)
		rotate_left(game);
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move_forward = 0;
	if (keycode == KEY_S)
		game->move_backward = 0;
	if (keycode == KEY_A)
		game->move_left = 0;
	if (keycode == KEY_D)
		game->move_right = 0;
	if (keycode == RIGHT)
		game->rotate_right = 0;
	if (keycode == LEFT)
		game->rotate_left = 0;
	return (0);
}
