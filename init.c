/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:12:58 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 11:34:47 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_init_moves(t_move *move)
{
    move->rotleft = 0;
    move->rotright = 0;
    move->backward = 0;
    move->forward = 0;
    move->right = 0;
    move->left = 0;
}

void    init_game(t_game *game, char **map, t_move *move)
{
    game->map = map;
    game->mlx = mlx_init();
    game->map_size_y = 0;
    while (map[game->map_size_y])
        game->map_size_y += 1;
    game->map_size_x = ft_strlen(map[0]);
    game->win = mlx_new_window(game->mlx, game->map_size_x * MAPWIDTH, game->map_size_y * MAPHEIGHT, "cub3D");
    game->img = mlx_new_image(game->mlx, game->map_size_x * MAPWIDTH, game->map_size_x * MAPHEIGHT);
    read_img(game);
    game->xc = (game->map_size_x * MAPWIDTH) / 2;
    game->yc = (game->map_size_y * MAPHEIGHT) / 2;
    game->angle = PI / 2;
    game->move = move;
}