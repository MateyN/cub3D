/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:00 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/05 10:48:02 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_press_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_W)
		game->player->move = +1;
	else if (keycode == KEY_S)
		game->player->move = -1;
	else if (keycode == KEY_D)
	{
		game->player->side = +1;
		game->player->side_pressed = 1;
	}
	else if (keycode == KEY_A)
	{
		game->player->side = -1;
		game->player->side_pressed = 1;
	}
	else if (keycode == RIGHT)
		game->player->rotdir = +1;
	else if (keycode == LEFT)
		game->player->rotdir = -1;
	return (0);
}

int	ft_release_key(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player->move = 0;
	else if (keycode == KEY_S)
		game->player->move = 0;
	else if (keycode == KEY_D)
	{
		game->player->side = 0;
		game->player->side_pressed = 0;
	}
	else if (keycode == KEY_A)
	{
		game->player->side = 0;
		game->player->side_pressed = 0;
	}
	else if (keycode == RIGHT)
		game->player->rotdir = 0;
	else if (keycode == LEFT)
		game->player->rotdir = 0;
	return (0);
}

int	ft_close(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	exit(EXIT_SUCCESS);
	return (0);
}
