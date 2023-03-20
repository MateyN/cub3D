/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:05 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/20 12:33:01 by mnikolov         ###   ########.fr       */
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
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define PI 3.14159265359
# define KeyPress 2
# define KeyRelease 3
# define MOVESPEED 1
# define ROTSPEED 0.05
# define MAPHEIGHT 25
# define MAPWIDTH 25

typedef struct	s_move
{
	int	rotleft;
	int	rotright;
	int	forward;
	int	backward;
	int	left;
	int	right;
}				t_move;

typedef struct s_game
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	void	*img;
	double	xc;
	double	yc;
	int		map_size_x;
	int		map_size_y;
	double	angle;
	t_move		*move;
}				t_game;

int		ft_press_key(int keycode, t_move *move);
int		ft_release_key(int keycode, t_move *move);

void	ft_free_ptr(char **ptr);
void    ft_cub3d(t_game *game, char **map);
void    init_game(t_game *game, char **map, t_move *move);
void    ft_init_moves(t_move *move);
int		ft_game(t_game *game);
void	fill_map(t_game *game);

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

int     ft_events(int keycode, t_game *game);
void	rot_left_right(t_game *game);
void    right_left_movement(t_game *game);
void    forward_backward_movement(t_game *game);
int 	ft_press_key(int keycode, t_move *move);
int		ft_key_release(int keycode, t_game *game);

void	draw_rays(t_game *game);
size_t	ft_strlen(const char *s);

void    render(t_game *game);

void    draw_player(t_game *game);
void	draw(t_game *game);

void    my_mlx_put_image_to_window(t_game *game, int x, int y, int color);
void 	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	read_img(t_game *game);
void	fill_map(t_game *game);

#endif