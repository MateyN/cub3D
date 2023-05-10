/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:32 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/05 10:46:53 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error("mlx_init", "Error: cannot initialize MLX library");
	game->win = mlx_new_window(game->mlx,
			MAPWIDTH, MAPHEIGHT, "cub3D");
	if (!game->win)
		exit_error("mlx_window", "Error: cannot open window");
	game->rays = malloc(sizeof(t_ray) * MAPWIDTH + 1);
	if (!game->rays)
		exit_strerr("malloc error", errno);
}

void	init_map(t_game *game)
{
	game->map->no = NULL;
	game->map->so = NULL;
	game->map->we = NULL;
	game->map->ea = NULL;
	game->map->floor = -1;
	game->map->ceiling = -1;
	game->map->width = 0;
	game->map->height = 0;
}

void	init_player(t_game *game)
{
	game->player->x = -1;
	game->player->y = -1;
	game->player->side = 0;
	game->player->move = 0;
	game->player->rotdir = 0;
	game->player->angle = 0;
	game->player->rotspeed = 0.05;
	game->player->movespeed = 5;
	game->player->side_pressed = 0;
	game->player->dist_proj_plane = (MAPWIDTH / 2) / tan(FOV / 2);
}

void	init_textures(t_game *game)
{
	game->sprites->no = draw_sprite(game->mlx, game->map->no);
	game->sprites->so = draw_sprite(game->mlx, game->map->so);
	game->sprites->we = draw_sprite(game->mlx, game->map->we);
	game->sprites->ea = draw_sprite(game->mlx, game->map->ea);
}

void	init_game(t_game *game)
{
	if (!game)
		exit_strerr("Error: malloc", 2);
	game->image = malloc(sizeof(t_img));
	game->sprites = malloc(sizeof(t_sprites));
	game->map = malloc(sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	game->map->map = ft_calloc(1, sizeof(char *));
	if (!game->image || !game->sprites || !game->map
		|| !game->player || !game->map->map)
		exit_strerr("Error: malloc", 2);
	init_map(game);
	init_player(game);
}
