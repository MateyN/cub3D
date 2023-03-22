/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:03:05 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/21 14:02:13 by mnikolov         ###   ########.fr       */
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
//# define COLLISION_STEP 0.01

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

	// FREE
void	ft_free_ptr(char **ptr);
void	free_game(t_game *game);

	// INIT
void    init_game(t_game *game, char **map, t_move *move);
void    ft_init_moves(t_move *move);

	// GAME
void    ft_cub3d(t_game *game, char **map);
int		ft_game(t_game *game);

	// LIBFT UTILS
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

	// MOVEMENT EVENTS
int		ft_press_key(int keycode, t_move *move);
int		ft_release_key(int keycode, t_move *move);
void	rot_left_right(t_game *game);
void    right_left_movement(t_game *game);
void    forward_backward_movement(t_game *game);

	// RAYCASTING
void	draw_rays(t_game *game);
void    draw_ray(t_game *game, double angle);

	//DRAW
void    draw_player(t_game *game);
void	draw_floor(t_game *game);
void	draw_walls(t_game *game);

	// RENDER
void    render(t_game *game);
void    my_mlx_put_image_to_window(t_game *game, int x, int y, int color);
void 	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	read_img(t_game *game);

#endif