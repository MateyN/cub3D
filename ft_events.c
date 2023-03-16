/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/16 12:45:14 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_buffer(t_game *game)
{
    game->buf.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    game->buf.addr = mlx_get_data_addr(game->buf.img, &game->buf.bits_per_pixel,
                                    &game->buf.line_length, &game->buf.endian);
}

void	draw_ray(t_game *game, double angle)
{
    double x;
    double y;

	x = game->xc;
	y = game->yc;
    while (1)
    {
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFFFF00);
        x += cos(angle) * 10;
        y += sin(angle) * 10;
        int i;
        int j;
		i = y / 25;
		j = x / 25;
        if (game->map[i][j] == '1')
            break ;
    }
}

void	draw_rays(t_game *game)
{
    double fov;
    double distperray; // calculate the angular distance between each ray that is cast from the player's position.

	fov = FOV;
	distperray = fov / (25 * game->map_size_x);
    while (fov / 2 > 0)
    {
        draw_ray(game, game->angle + (fov / 2));
        draw_ray(game, game->angle - (fov / 2));
        fov -= distperray;
    }
}

void ft_move(int i, int x, int y, t_game *game)
{
	(void)i;
    if (game->map[y / 25][x / 25] == '1') // check the exact cell that the player is in
        return ;
    game->xc = x;
    game->yc = y;
    mlx_clear_window(game->mlx, game->win); // clear the window before re-drawing
    fill_map(game); // draw the map only once
    draw_rays(game); // cast all rays asynchronously
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

int ft_events(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        exit(EXIT_SUCCESS);
    if (keycode == KEY_W)
        ft_move(0, game->xc + (10 * cos(game->angle)), game->yc + (10 * sin(game->angle)), game);
    if (keycode == KEY_S)
        ft_move(1, game->xc - (10 * cos(game->angle)), game->yc - (10 * sin(game->angle)), game);
    if (keycode == KEY_A)
        ft_move(2, game->xc - (10 * sin(game->angle)), game->yc + (10 * cos(game->angle)), game);
    if (keycode == KEY_D)
        ft_move(3, game->xc + (10 * sin(game->angle)), game->yc - (10 * cos(game->angle)), game);
    if (keycode == RIGHT)
        rotate_right(game);
    if (keycode == LEFT)
        rotate_left(game);
    return (0);
}

int ft_key_release(int keycode, t_game *game)
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