/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:04:20 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/22 16:29:47 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_game(t_game *game)
{
    rot_left_right(game);
    if (game->move->right || game->move->left)
        right_left_movement(game);
    if (game->move->forward || game->move->backward)
        forward_backward_movement(game);
    render(game);   
    return (0);
}

void    ft_cub3d(t_game *game, char **map)
{
    t_move  move;

    ft_init_moves(&move);
    init_game(game, map, &move);
    mlx_hook(game->win, KEYPRESS, 1L << 0, ft_press_key, &move);
	mlx_loop_hook(game->mlx, ft_game, game);
	mlx_hook(game->win, KEYRELEASE, 1L << 1, ft_release_key, &move);
	mlx_loop(game->mlx);
}