/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 10:45:41 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left_right(t_game *game)
{
	if (game->move->rotright == 1)
		game->angle += ROTSPEED;
	if (game->move->rotleft == 1)
		game->angle -= ROTSPEED;
}

void    right_left_movement(t_game *game)
{
    double tmp_x;
    double tmp_y;

    tmp_x = game->xc;
    tmp_y = game->yc;
    if (game->move->right == 1)
    {
        game->xc -= MOVESPEED * sin(game->angle);
        game->yc += MOVESPEED * cos(game->angle);
    }
    if (game->move->left == 1)
    {
        game->xc += MOVESPEED * sin(game->angle);
        game->yc -= MOVESPEED * cos(game->angle);
    }
    if (game->map[(int)((game->yc + 3) / MAPHEIGHT)][(int)((game->xc + 3) / MAPWIDTH)] == '1'
        || game->map[(int)((game->yc - 3) / MAPHEIGHT)][(int)((game->xc - 3) / MAPWIDTH)] == '1')
    {
        game->xc = tmp_x;
        game->yc = tmp_y;
    }
}

void    forward_backward_movement(t_game *game)
{
    double tmp_x;
    double tmp_y;

    tmp_x = game->xc;
    tmp_y = game->yc;
    if (game->move->forward == 1)
    {
        game->xc += MOVESPEED * cos(game->angle);
        game->yc += MOVESPEED * sin(game->angle);
    }
    if (game->move->left == 1)
    {
        game->xc -= MOVESPEED * cos(game->angle);
        game->yc -= MOVESPEED * sin(game->angle);
    }
    if (game->map[(int)((game->yc + 3) / MAPHEIGHT)][(int)((game->xc + 3) / MAPWIDTH)] == '1'
        || game->map[(int)((game->yc - 3) / MAPHEIGHT)][(int)((game->xc - 3) / MAPWIDTH)] == '1')
    {
        game->xc = tmp_x;
        game->yc = tmp_y;
    }
}

int ft_press_key(int keycode, t_move *move)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_W)
		move->forward = 1;
	if (keycode == KEY_S)
		move->backward = 1;
	if (keycode == KEY_D)
		move->right = 1;
	if (keycode == KEY_A)
		move->left = 1;
	if (keycode == RIGHT)
		move->rotright = 1;
	if (keycode == LEFT)
        move->rotleft = 1;
	return (0);
}

int ft_release_key(int keycode, t_move *move)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_W)
		move->forward = 0;
	if (keycode == KEY_S)
		move->backward = 0;
	if (keycode == KEY_D)
		move->right = 0;
	if (keycode == KEY_A)
		move->left = 0;
	if (keycode == RIGHT)
		move->rotright = 0;
	if (keycode == LEFT)
        move->rotleft = 0;
	return (0);
}