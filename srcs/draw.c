/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:23:38 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 13:47:07 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_wall(t_game *game, t_wall wall, t_img *wall_texture, int i)
{
	int     j;
	char    *dst;

	j = 0;
	while (j < wall.draw_y)
	    my_mlx_pixel_put(game->image, i, j++, game->map->ceiling);  
	while (j < wall.draw_x)
	{
		wall.draw = j + (wall.wall_height / 2) - (MAPHEIGHT / 2);
		wall.texture_y = (int)(wall.draw
				* (float)wall_texture->height / wall.wall_height)
			% wall_texture->height;
		dst = wall_texture->addr + wall.texture_y * wall_texture->line_length
			+ wall.texture_x * (wall_texture->bits_per_pixel / 8);
		my_mlx_pixel_put(game->image, i, j++, *(unsigned int *)dst);
	}
	while (j < MAPHEIGHT)
		my_mlx_pixel_put(game->image, i, j++, game->map->floor);
}

void    draw_player(t_game *game, char **map, int y, int x)
{
	if (game->player->x != -1 || game->player->y != -1)
		exit_str("Duplicate player");
	game->player->x = (x * TILES) + 14;
	game->player->y = (y * TILES) + 14;
	if (map[y][x] == 'N')
	    game->player->angle = 270 * (PI / 180);   
	else if (map[y][x] == 'S')
		game->player->angle = 90 * (PI / 180);    
	else if (map[y][x] == 'W')
		game->player->angle = 180 * (PI / 180);
	else if (map[y][x] == 'E')
		game->player->angle = 0 * (PI / 180);
	game->map->map[y][x] = '0';
}

t_img   *draw_sprite(void *mlx, char *path)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		exit_strerr("malloc", 2);
	sprite->img = mlx_xpm_file_to_image(mlx, path,
		    &sprite->width, &sprite->height);   
	if (!sprite->img)
		exit_strerr(path, 2);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian); 
	return (sprite);
}