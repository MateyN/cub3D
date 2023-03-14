/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:05 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/13 14:32:00 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define FOV 1.04719755 // 60 degree
# define RIGHT 124
# define LEFT 123

typedef struct s_game
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	int		xc;
	int		yc;
	int		a;
	int		s;
	int		w;
	int		d;
	int		left;
	int		right;
	int		map_size_x;
	int		map_size_y;
	double	angle;
	int		win_width;
}				t_game;

typedef struct s_ray
{
    double	angle;
    double	distance;
    int		hit;
    double	x;
    double	y;
}				t_ray;

void	ft_free_ptr(char **ptr);
void	ft_game(t_game *game);
void	fill_map(t_game *game);
void	draw_pixel(t_game *game);

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

int     ft_events(int keycode, t_game *game);
size_t	ft_strlen(const char *s);

void	read_img(t_game *game);
void	fill_map(t_game *game);

#endif