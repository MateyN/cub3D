/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:26:02 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/07 12:13:33 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "cub3d.h"

#include <stdlib.h>
#include <stdio.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SQUARE_SIZE 200

void	init(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Test");
    data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    data->img_data = (int *)mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel, &data->size_line, &data->endian);
}

void	set_background_color(t_data *data)
{
    int x;
	int	y;

	x = 0;
	y = 0;
    while (y < WIN_HEIGHT / 2)
	{
        x = 0;
        while (x < WIN_WIDTH)
		{
            data->img_data[y * WIN_WIDTH + x] = 0x0000FF;
            x++;
        }
        y++;
    }

    while (y < WIN_HEIGHT)
	{
        x = 0;
        while (x < WIN_WIDTH)
		{
            data->img_data[y * WIN_WIDTH + x] = 0x00FF00;
            x++;
        }
        y++;
    }
}

void draw_square(t_data *data)
{
	int x;
	int y;
	
	int square_x = (WIN_WIDTH - SQUARE_SIZE) / 2;
	int square_y = (WIN_HEIGHT - SQUARE_SIZE) / 2;
	y = square_y;
	while (y < square_y + SQUARE_SIZE)
	{
		x = square_x;
	while (x < square_x + SQUARE_SIZE)
	{
		data->img_data[y * WIN_WIDTH + x] = 0xFF0000;
		x++;
	}
	y++;
	}
}

void	display_image(t_data *data)
{
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}

void	set_hooks(t_data *data)
{
    mlx_hook(data->win_ptr, 17, 0, exit, 0);
    mlx_hook(data->win_ptr, 2, 0, exit, 0);
}

int	main()
{
    t_data	data;

    init(&data);
    set_background_color(&data);
    draw_square(&data);
    display_image(&data);
    set_hooks(&data);
    mlx_loop(data.mlx_ptr);
    return (0);
}