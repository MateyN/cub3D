/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:07 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/14 10:27:37 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		exit_success("Wrong usage! -> ./cub3D maps/<map.cub>");
	game = (t_game *)malloc(sizeof(t_game));
	parsing(game, av[1]);
	init_window(game);
	init_textures(game);
	ft_game(game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
