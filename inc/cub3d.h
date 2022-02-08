/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:20:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 14:34:25 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* standard unix library */
# include <unistd.h>

/* open() */
# include <fcntl.h>

/* math */
# include <math.h>

/* minilibx */
# include <mlx.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* our own implementation of libc */
# include <libft.h>

/* program */
# ifndef NAME
#  define NAME "cub3d"
# endif

/* window resolution */
# ifndef WIN_W
#  define WIN_W 1280
# endif
# ifndef WIN_H
#  define WIN_H 720
# endif

/* minimap scale --> ?:1 */
# define MINIMAP_SCALE 10
/* minimap border offset % */
# define MM_OFFSET 2

/* textures */
# if !defined TEX_W || !defined TEX_H
#  define TEX_W 64
#  define TEX_H 64
# endif
# if !defined NO || !defined SO || !defined WE || !defined EA || !defined DOOR
#  define TEX_NO 0
#  define TEX_SO 1
#  define TEX_WE 2
#  define TEX_EA 3
#  define TEX_DOOR 4
# endif

/* other useful macros */
# define FLOOR '0'
# define WALL '1'
# define DOOR_OPEN 'O'
# define DOOR_CLOSE 'C'
# define DEFAULT_SPEED 0.1
# define DEFAULT_ROT_SPEED 0.1
# define Y 0
# define X 1
# define TEXT_COLOR 0xFFFFFF
# define CROSSHAIR_COLOR 0xFFFFFF
# define MINIMAP_PLAYER 0xFF0000
# define MINIMAP_WALL 0x1E2328
# define MINIMAP_FLOOR 0x3B3F46
# define MINIMAP_DOOR 0xF5B301

/* minilibx keymaps */
# ifdef OSX
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_MINUS 27
#  define KEY_PLUS 24
#  define KEY_R 15
#  define KEY_U 32
#  define KEY_J 38
#  define KEY_I 34
#  define KEY_K 40
#  define KEY_O 31
#  define KEY_L 37
#  define KEY_E 14
# else
#  ifndef LINUX
#   define LINUX
#  endif
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_P 112
#  define KEY_MINUS 45
#  define KEY_PLUS 61
#  define KEY_R 114
#  define KEY_U 117
#  define KEY_J 106
#  define KEY_I 105
#  define KEY_K 107
#  define KEY_O 111
#  define KEY_L 108
#  define KEY_E 101
# endif

/* PARSER DEFINES */
# define BS "BEGIN SPRITES"
# define ES "END SPRITES"
# define BP "BEGIN POS"
# define EP "END POS"
/* s_map: map struct
 *
 * res[2]	-> resolution of the window defined on the map file
 * *NO, *SO, *WE, *EA	-> path to the different wall textures
 * *S		-> sprite texture path
 * *fRGB	-> floor rgb colors
 * *cRGB	-> ceiling rgb colors
 * *p_pos	=> Player position -> [0] = x, [1] = y;
 */

typedef struct s_sprite
{
	int		x;
	int		y;
	int		id;
}	t_sprite;

typedef struct s_spaux
{
	char	*type;
	int		id;
}	t_spaux;

typedef struct s_map
{
	t_sprite	*sprite;
	t_spaux		*spaux;
	char		start_orientation;
	char		**map;
	char		**buffer;
	char		***sprites;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*door;
	int			width;
	int			height;
	int			frgb;
	int			sprite_index;
	int			sprite_cnt;
	int			pos_index;
	int			pos_cnt;
	int			crgb;
	int			aux;
	int			lines;
	int			index;
	int			count;
	float		p_pos[2];
}	t_map;

/* s_img: minilibx image struct
 *
 * *img		-> pointer to the image
 * *addr	-> pointer to the pixels data
 * bpp		-> bits per pixel
 * line_len -> len of a line of pixeles in *addr
 * endian	-> SO endian type (0 = small endian, 1 = big endian)
 */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex {
	t_img	img;
	int		h;
	int		w;
}	t_tex;

/* s_p: player struct */
typedef struct s_p
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_p;

/* s_vars: program struct */
typedef struct s_vars {
	int			frame;
	t_map		map;
	t_p			p;
	t_img		img;
	t_img		minimap;
	t_img		mm_player;
	int			mm_offset[2];
	t_tex		tex[5];
	t_tex		***sprite;
	t_sprite	**sprites;
	void		*mlx;
	void		*win;
	int			door_hit[2];
}	t_vars;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	float	cam_x;
	float	cam_y;
	float	dir_x;
	float	dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		hit_door;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_id;
	int		tex_x;
	int		tex_y;
	float	wall_x;
	float	step;
	float	tex_pos;
	float	z_buffer[WIN_W];
	int		*sprite_order;
	float	*sprite_dist;
}	t_ray;

/* sprite support struct */
typedef struct s_sprite_sp {
	float	x;
	float	y;
	float	inv_det;
	float	transform_x;
	float	transform_y;
	int		screen_x;
	int		height;
	int		draw_start_y;
	int		draw_end_y;
	int		width;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		d;
	int		tex_y;
	int		color;
	int		id;
	int		frame;
}	t_sprite_sp;

/* parse_map.c */

/* main_parse.c */
int		first_read(char *str, t_map *map);
int		init_parser(t_map *map, char *str);

/* parse_config.c */
int		parse_textures(t_map *map);

/* parse_map.c */
int		parse_map(t_map **map);
int		free_struct(t_map *map, int ret);
int		is_dptr_digit(char **s);
int		create_trgb(int t, int r, int g, int b);
int		process_colour(t_map **map, int i, char **sp);
int		last_map_check(t_map **map);
int		check_surroundings(t_map **map, int i, int j);

/* parse_utils.c */
int		check_format(char *str);

/* error_utils.c */
void	perror_exit(const char *s);
int		perror_ret(const char *s, int ret_code);
int		error_ret(const char *s, int ret_code);

/* utils_1.c */
void	free_split(char **split);
void	free_vars(t_vars *vars);
void	free_all(t_vars *vars);
int		initialise_vars(t_vars *vars);

/* utils_2.c */
int		dptr_len(char **s);
void	init_map(t_map	*map);

/* mlx_main.c */
int		mlx_main(t_vars *vars);

/* mlx_hook.c */
int		close_win(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

/* mlx_init.c */
int		initialise_mlx(t_vars *vars);

/* minimap.c */
void	initialise_minimap(t_vars *vars);

/* mlx_utils.c */
int		get_pixel_color(t_img *img, int x, int y);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	img_paste_pixel(t_img *img, int x, int y, int pixel);

/* mlx_loop.c */
int		game_loop(void *vars);

/* mlx_controls.c */
void	handle_move(int keycode, t_vars *vars, float speed);
void	handle_sidemove(int keycode, t_vars *vars, float speed);
void	handle_look(int keycode, t_vars *vars, float speed);
void	handle_door(t_vars *vars);

/* mlx_textures.c */
int		init_textures(t_vars *vars);

/* player.c */
int		player_init(t_vars *vars);

/* draw.c */
void	draw(t_vars *vars);

/* raycast_sprite.c */
void	raycast_sprite(t_vars *vars, t_ray *ray);

#endif
