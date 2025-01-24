/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:44:29 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/24 20:00:45 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "./libft.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.141592654
# define MINIMAP_SCALE 10
# define MINIMAP_SIZE 100
# define MINIMAP_START_X 10
# define MINIMAP_START_Y 10

typedef struct s_graphics
{
	int				resolution;
	int				texture_north;
	int				texture_south;
	int				texture_east;
	int				texture_west;
	int				sprite_texture;
	int				floor_color;
	int				skying_color;
}					t_graphics;

typedef struct s_resolution
{
	int				width;
	int				height;
}					t_resolution;

typedef struct s_texture
{
	char			*path;
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_sprite
{
	char			*path;
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				endian;
	int				width;
	int				height;
	int				tot;
	double			**buf;
	double			*zbuf;
	double			*dist;
	double			*order;
	double			dir_x;
	double			dir_y;
	double			posx;
	double			posy;
	int				screenx;
	int				startx;
	int				endx;
	int				starty;
	int				endy;
	int				modify;
	int				width2;
}					t_sprite;

typedef struct s_color
{
	char			*skying;
	char			*floor;
	int				cl_red;
	int				cl_green;
	int				cl_blue;
	int				fl_red;
	int				fl_green;
	int				fl_blue;

}					t_color;

typedef struct s_texture_element
{
	t_graphics		graphics;
	t_resolution	resolution;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		west_texture;
	t_texture		east_texture;
	t_sprite		sprite;
	t_color			color;
}					t_texture_element;

typedef struct s_map_data
{
	char			**matrix;
	int				width;
	int				height;
	int				player;
}					t_map_data;

typedef struct s_player_data
{
	double			posx;
	double			posy;
	double			dir_x;
	double			dir_y;
	double			lirx;
	double			liry;
	double			plnx;
	double			plny;
}					t_player_data;

typedef struct s_rayc
{
	double			dir_x;
	double			dir_y;
	double			sdistx;
	double			sdisty;
	double			ddistx;
	double			ddisty;
	double			stepx;
	double			stepy;
	double			wall_dist;
	double			lineh;
}					t_rayc;

typedef struct s_map_content
{
	char			**board;
	int				x;
	int				y;
	int				side;
	int				sky;
	int				wall;
	int				floor;
	int				width;
	int				height;
}					t_map_content;

typedef struct s_textures
{
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
}					t_textures;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				length;
	int				end;
}					t_mlx;

typedef struct s_key
{
	int				move_up;
	int				move_down;
	int				move_left;
	int				move_right;
	int				rot_left;
	int				rot_right;
	int				destroy;
}					t_key;

typedef struct s_data
{
	int				screen_w;
	int				screen_h;
	t_player_data	ply;
	t_rayc			ray;
	t_map_content	map;
	t_textures		tex;
	t_mlx			mlx;
	t_key			key;
	t_texture		nor;
	t_texture		sou;
	t_texture		eas;
	t_texture		wes;
	t_sprite		spr;
	t_map_data		map_d;
}					t_data;

typedef struct s_coords
{
	int				map_x;
	int				map_y;
	int				real_x;
	int				real_y;
}					t_coords;

/* main.c */
t_map_data			*get_map_data(void);
void				ft_error(char *str, char *line);

/* errors.c */
void				check_elem_texture(const char *str,
						t_texture_element *elems);

/* error_txts.c */
void				error_north(char **line, t_texture_element *elems);
void				error_south(char **line, t_texture_element *elems);
void				error_west(char **line, t_texture_element *elems);
void				error_east(char **line, t_texture_element *elems);
void				error_sprite(char **line, t_texture_element *elems);

/* error_colres.c */
void				copy_path(int count, char **str, char **line);
void				error_resolution(char **line, t_texture_element *elems);
void				error_floor(char **line, t_texture_element *elems);
void				error_skying(char **line, t_texture_element *elems);

/* error_map.c */
void				check_validate_map(const char *map_use,
						t_map_data *map_data);

/* error_imap.c */
void				create_map(const char *str, t_map_data *map_data);

/* read_map.c */
void				validate_map_first_line(char **line, t_map_data *map_data);
void				validate_map_lines(int fd, char **line,
						t_map_data *map_dat);
void				validate_map_last_line(char *line, t_map_data *map_data);

/* validate_map_lines.c */
void				map_space(int pos, int count_x, t_map_data *map_data, char **line);
void				map_other(int pos, int count_x, char **line,
						t_map_data *map_data);
void				map_x(int pos, int count_x, t_map_data *map_data, char **line);

/* cub.c  */
void				cub(t_texture_element *elems, t_map_data *map_data);

/* findspr.c */
void				find_sprites(t_data *dsp_dt, t_map_data *map_data);
void				sort_sprites(double *order, double *dist, int tot, int idx);

/* renderframe.c */
int					render_frame(t_data *dsp_dt);

/* textures.c */
void				north_texture(t_data *dsp_dt);
void				south_texture(t_data *dsp_dt);
void				east_texture(t_data *dsp_dt);
void				west_texture(t_data *dsp_dt);
void				sprite_texture(t_data *dsp_dt);

/* texel.c */
void				buff_no_wall(int x, int **buffer, t_data *dsp_dt);
void				find_tex_x(t_data *dsp_dt);
void				find_tex_pos(t_data *dsp_dt);
void				buff_wall(int x, int **buffer, t_data *dsp_dt);

/* sprites.c */
void				sprites(int **buffer, t_data *dsp_dt);

/* setdir.c */
void				set_dir(char c, t_data *dsp_dt);

/* keypress.c */
int					key_press(int keycode, t_data *dsp_dt);
int					key_release(int keycode, t_data *dsp_dt);

/* change_move.c */
void				adv_move(double move, t_data *dsp_dt);
void				back_move(double move, t_data *dsp_dt);
void				dsp_left(double move, t_data *dsp_dt);
void				dsp_right(double move, t_data *dsp_dt);
void				update_player_movement(t_data *dsp_dt);

/* change_rot.c */
void				rot_right(double rot, t_data *dsp_dt);
void				rot_left(double rot, t_data *dsp_dt);

/* error_utils.c */
void				validate_image_path(char *path);
int					look_color(int *red, int *green, char *color);

/* utils.c */
t_data				*get_dsp_data(void);
void				my_mlx_pixel_put(t_data *dsp_dt, int x, int y, int color);
void				init_buffer(int mode, int ***buffer, t_data *dsp_dt);
void				draw_buffer(int **buffer, t_data *dsp_dt);
void				draw_sprites(int height, int **buffer, t_data *dsp_dt);

/* minimap_bonus.c */
void				bonus_draw_minimap(t_data *dsp);
void				bonus_draw_minimap_player(t_data *dsp);

/* mouse_bonus.c */
void				bonus_init_mouse(t_data *dsp_dt);

#endif
