/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:23:38 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/20 15:08:59 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
@brief This function draws a wall on the screen with the given texture.
@param game A pointer to the main game struct.
@param wall A struct containing information about the wall being drawn.
@param wall_texture A pointer to the texture used to draw the wall.
@param i The index of the ray being cast for the wall being drawn.
*/
void draw_wall(t_game *game, t_wall wall, t_img *wall_texture, int i)
{
	int		j;
	char	*dst;
	// Draw the ceiling up to the top of the wall
	j = 0;
	while (j < wall.draw_y)
		my_mlx_pixel_put(game->image, i, j++, game->map->ceiling);
		// Draw the wall itself
	while (j < wall.draw_x)
	{
	// Calculate the height of the wall to draw, and the corresponding texture position
		wall.draw = j + (wall.wall_height / 2) - (MAPHEIGHT / 2); // Putting the wall vertically on the screen
		wall.texture_y = (int)(wall.draw
			* (float)wall_texture->height / wall.wall_height)
				% wall_texture->height; // Taking the right texture coordinate and wrap it in with modulo 
				// to be within the range of the texture and the wall
		// Calculate the position in memory of the texture pixel to draw
		dst = wall_texture->addr + wall.texture_y * wall_texture->line_length
			+ wall.texture_x * (wall_texture->bits_per_pixel / 8);
		my_mlx_pixel_put(game->image, i, j++, *(unsigned int *)dst);
	}
	// Draw the floor below the wall
	while (j < MAPHEIGHT)
		my_mlx_pixel_put(game->image, i, j++, game->map->floor);
}

/**
@brief Draws the player on the game screen.
@param game The game struct.
@param map The game map.
@param y The y position of the player on the map.
@param x The x position of the player on the map.
*/
void draw_player(t_game *game, char **map, int y, int x)
{
    // Check if a player has already been created
    if (game->player->x != -1 || game->player->y != -1)
        exit_str("Duplicate player");
    // Calculate player's x and y position on the game screen based on the map
    game->player->x = (x * TILES) + 16;
    game->player->y = (y * TILES) + 16;
    // Set the player's angle based on the direction it's facing
    if (map[y][x] == 'N')
        game->player->angle = 270 * (PI / 180); // converting radians into degrees to indicate which way the player is facing
    else if (map[y][x] == 'S')
        game->player->angle = 90 * (PI / 180);
    else if (map[y][x] == 'W')
        game->player->angle = 180 * (PI / 180);
    else if (map[y][x] == 'E')
        game->player->angle = 0 * (PI / 180);
    // Update the map to remove the player from its previous position
    game->map->map[y][x] = '0';
}

t_img   *draw_sprite(void *mlx, char *path)
{
	t_img	*sprite;

	sprite = malloc(sizeof(t_img));
	if (!sprite)
		exit_strerr("error: malloc", 2);
	sprite->img = mlx_xpm_file_to_image(mlx, path,
		    &sprite->width, &sprite->height);   
	if (!sprite->img)
		exit_strerr(path, 2);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian); 
	return (sprite);
}