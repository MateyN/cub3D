/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:15 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/23 13:05:08 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int is_valid_move(t_game *game, double new_x, double new_y)
{
    // Calculate the cell indices of the new position
    int cell_x = (int)(new_x / MAPWIDTH);
    int cell_y = (int)(new_y / MAPHEIGHT);

    // Check if the new position is outside the map
    if (cell_x < 0 || cell_x >= MAPWIDTH || cell_y < 0 || cell_y >= MAPHEIGHT)
    {
        // The new position is outside the map, so it is an invalid move
        return 0;
    }

    // Check if the new position is a wall
    if (game->map[cell_y][cell_x] == '1')
    {
        // The new position is a wall, so it is an invalid move
        return 0;
    }

    // Cast a ray from the player's current position towards the new position
    double ray_x = game->xc;
    double ray_y = game->yc;
    double ray_dx = new_x - ray_x;
    double ray_dy = new_y - ray_y;
    double ray_len = sqrt(ray_dx * ray_dx + ray_dy * ray_dy);
    ray_dx /= ray_len;
    ray_dy /= ray_len;

    // Step along the ray in small increments, checking for collisions with walls
    for (double step = 0; step <= ray_len; step += COLLISION_STEP)
    {
        // Calculate the coordinates of the current point along the ray
        double point_x = ray_x + ray_dx * step;
        double point_y = ray_y + ray_dy * step;

        // Calculate the cell indices of the current point
        int point_cell_x = (int)(point_x / MAPWIDTH);
        int point_cell_y = (int)(point_y / MAPHEIGHT);

        // Check if the current point is a wall
        if (game->map[point_cell_y][point_cell_x] == '1')
        {
            // The ray has collided with a wall, so the new position is an invalid move
            return 0;
        }
    }

    // The new position is a valid move
    return 1;
}
*/

void	rot_left_right(t_game *game)
{
	if (game->move->rotright == 1)
		game->angle += ROTSPEED;
	if (game->move->rotleft == 1)
		game->angle -= ROTSPEED;
}

void    right_left_movement(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->xc;
    new_y = game->yc;
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
    // if (is_valid_move(game, new_x, new_y))
    if (game->map[(int)((game->yc + 3) / MAPHEIGHT)][(int)((game->xc + 3) / MAPWIDTH)] == '1'
        || game->map[(int)((game->yc - 3) / MAPHEIGHT)][(int)((game->xc - 3) / MAPWIDTH)] == '1')
    {
        game->xc = new_x;
        game->yc = new_y;
    }
}

void    forward_backward_movement(t_game *game)
{
    double new_x;
    double new_y;

    new_x = game->xc;
    new_y = game->yc;
    if (game->move->forward == 1)
    {
        game->xc += MOVESPEED * cos(game->angle);
        game->yc += MOVESPEED * sin(game->angle);
    }
    if (game->move->backward == 1)
    {
        game->xc -= MOVESPEED * cos(game->angle);
        game->yc -= MOVESPEED * sin(game->angle);
    }
    // if (is_valid_move(game, new_x, new_y))
    if (game->map[(int)((game->yc + 3) / MAPHEIGHT)][(int)((game->xc + 3) / MAPWIDTH)] == '1'
        || game->map[(int)((game->yc - 3) / MAPHEIGHT)][(int)((game->xc - 3) / MAPWIDTH)] == '1')
    {
        game->xc = new_x;
        game->yc = new_y;
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