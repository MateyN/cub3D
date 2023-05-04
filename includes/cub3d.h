/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:12:46 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/04 12:35:04 by mnikolov         ###   ########.fr       */
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
# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <string.h>
# include "get_next_line.h"

# define FOV 60 * (M_PI / 180)
# define PI 3.14159265358979323846264338327950288
# define ANGLE_90 (PI / 2)
# define ANGLE_270 (3 * PI / 2)
# define RIGHT 124
# define LEFT 123
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define MAPHEIGHT 760
# define MAPWIDTH 1280
# define TILES 32

enum e_ELEMENTS
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	ERROR,
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		move;
    int     side;
	float	movespeed;
	int		rotdir;
	float	rotspeed;
	float	dist_proj_plane;
}	t_player;

typedef struct s_wall
{
	int		draw;
	int		texture_x;
	int		texture_y;
	float	draw_y;
	float	draw_x;
	float	wall_height;
	float	corr_dist;
}	t_wall;

typedef struct s_intersection
{
	float	deltaX;
	float	deltaY;
	float	wall_interX;
	float	wall_interY;
	float	currentX;
	float	currentY;
	float	hit_dist;
	int		wall_hit;
}	t_intersection;

typedef struct s_ray
{
	float	angle;
	float	hit_x;
	float	hit_y;
	float	dist;
	int		vert_hit;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
}	t_ray;

typedef struct s_sprites
{
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}	t_sprites;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	int		map_size_x;
	int		map_size_y;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		*image;
	t_ray		*rays;
	t_map		*map;
	t_player	*player;
	t_sprites	*sprites;
}	t_game;

// ----------------------------  PARSING  ---------------------------- //

void	parsing(t_game *game, char *str);
void	file_checker(char *str, char *extension);
void	file_parsing(t_game *game, int fd);
void	texture_parsing(t_game *game, char *line, int token, int i);
void	map_parsing(t_game *game, char *line, int fd);

// --------------------------  LINE PARSING  ------------------------- //

int		line_parsing(t_game *game, char *line);
void	color_parsing(t_game *game, char *line, int token, int i);
int		player_direction(char c);
void	check_length(char *line);
int		set_map(t_game *game);

// --------------------------  MAP PARSING  ------------------------- //

void	ft_isspaces(char *s, int *i);
int		is_map(char *line);
int		check_name(char *name);
int		check_args(char **args);
char	**add_map(char **strs, char *arg);
void	check_map(t_game *game);
void	check_map_borders(char **map);
void	check_map_content(t_game *game, char **map);

// --------------------------  INITIALIZING  ------------------------- //
void	init_map(t_game *game);
void	init_game(t_game *game);
void	init_player(t_game *game);
void	init_window(t_game *game);
void	init_textures(t_game *game);

// -----------------------------  FREE  ----------------------------- //

void	ft_free_ptr(char **ptr);

// -----------------------------  GAME  ----------------------------- //

void	ft_game(t_game *game);
void	set_hooks(t_game *game);
void	set_game(t_game *game);
void	update(t_game *game);
int		loop_hook(t_game *game);

// ---------------------------  RENDER  --------------------------- //

void	render_3d_wall(t_game *game, int i, t_wall wall);
void	render_3d_view(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	render(t_game *game);

// ---------------------------  RAYCASTING  --------------------------- //

void			draw_rays(t_game *game);
void			draw_ray(t_game *game, float angle, int i);
void			fill_ray(t_ray *ray, t_intersection *dir, int boolean);
t_intersection	*draw_vert(t_game *game, float angle, int i);
t_intersection	*draw_horz(t_game *game, float angle, int i);

// ---------------------------  RAYCASTING UTILS --------------------------- //

double	get_dist_to_wall(t_game *game, t_intersection *dir);
double	calc_wall_dist(double x1, double y1, double x2, double y2);
void	dda_hor_step(t_game *game, t_intersection *h, int i);
void	dda_vert_step(t_game *game, t_intersection *v, int i);

// -----------------------------  MOVEMENT ------------------------------ //

int		ft_press_key(int keycode, t_game *game);
int		ft_release_key(int keycode, t_game *game);
int		ft_close(int keycode, t_game *game);

// -----------------------------  DRAW ------------------------------ //

t_img	*draw_sprite(void *mlx, char *path);
void	draw_wall(t_game *game, t_wall wall, t_img *texture, int i);
void	draw_player(t_game *game, char **map, int y, int x);

// -----------------------------  MOVEMENT UTILS ------------------------------ //

void	move_player(t_game *game);
int		can_move(t_map *map, double x, double y);
int		get_width(char *line);

// -----------------------------  EXITS  ----------------------------- //

void	exit_str(char *str);
void	exit_success(char *str);
void	exit_error(char *str, char *err);
void	exit_strerr(char *str, int err);

#endif
