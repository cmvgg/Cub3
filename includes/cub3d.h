#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "./libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
#include <stdbool.h>

# define PI 3.141592654
# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361

typedef struct s_element_counter {
    int resolution;
    int north_texture;
    int south_texture;
    int east_texture;
    int west_texture;
    int sprite;
    int floor_color;
    int ceiling_color;
} t_element_counter;

typedef struct s_resolution {
    int width;
    int height;
} t_resolution;

typedef struct s_texture {
    char    *path;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_texture;

typedef struct s_sprite {
    t_texture   texture;
    int         total;
    double      **buffer;
    double      *z_buffer;
    double      *distance;
    double      *order;
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    int         screen_x;
    int         start_y;
    int         end_y;
    int         start_x;
    int         end_x;
} t_sprite;

typedef struct s_color {
    char    *floor;
    char    *ceiling;
    int     floor_rgb[3];
    int     ceiling_rgb[3];
} t_color;

typedef struct s_game_elements {
    t_element_counter  counter;
    t_resolution       resolution;
    t_texture          north;
    t_texture          south;
    t_texture          west;
    t_texture          east;
    t_sprite           sprite;
    t_color            color;
} t_game_elements;

typedef struct s_map {
    char    **grid;
    int     width;
    int     height;
    int     player_count;
} t_map;

typedef struct s_player {
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
} t_player;

typedef struct s_ray {
    double  dir_x;
    double  dir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  step_x;
    double  step_y;
    double  wall_dist;
    double  line_height;
} t_ray;

typedef struct s_map_info {
    char    **world;
    int     map_x;
    int     map_y;
    int     side;
    int     ceiling_color;
    int     wall_color;
    int     floor_color;
} t_map_info;

typedef struct s_texture_info {
    double  wall_x;
    double  step;
    double  tex_pos;
    int     tex_x;
    int     tex_y;
} t_texture_info;

typedef struct s_mlx_info {
    void    *mlx;
    void    *window;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_mlx_info;

typedef struct s_key_state {
    int     move_up;
    int     move_down;
    int     move_left;
    int     move_right;
    int     rotate_left;
    int     rotate_right;
    int     exit_game;
} t_key_state;

typedef struct s_game_data {
    int             screen_width;
    int             screen_height;
    t_player        player;
    t_ray           ray;
    t_map_info      map;
    t_texture_info  texture;
    t_mlx_info      mlx;
    t_key_state     key;
    t_texture       north;
    t_texture       south;
    t_texture       east;
    t_texture       west;
    t_sprite        sprite;
} t_game_data;

/* input */
/* player_movement.c */
void	move_player_forward(double move_speed, t_game_data *game_data);
void	move_player_backward(double move_speed, t_game_data *game_data);
void	move_player_left(double move_speed, t_game_data *game_data);
void	move_player_right(double move_speed, t_game_data *game_data);
void	update_player_position(t_game_data *game_data);

/* player_rotation.c */
void	rotate_player_right(double rotation_speed, t_game_data *game_data);
void	rotate_player_left(double rotation_speed, t_game_data *game_data);

/* render */
/* frame_renderer.c */
int		render_game_frame(t_game_data *game_data);

/* sprite_handler.c */
void	render_sprites(int **buffer, t_game_data *game_data);

/* texture_manager.c */
void	load_north_texture(t_game_data *game_data);
void	load_south_texture(t_game_data *game_data);
void	load_east_texture(t_game_data *game_data);
void	load_west_texture(t_game_data *game_data);
void	load_sprite_texture(t_game_data *game_data);

/* map */
/* map_parser.c */
void	parse_map_first_line(char **line, t_map *map_data);
void	parse_map_body(int fd, char **line, t_map *map_data);
void	parse_map_last_line(char **line, t_map *map_data);

/* map_validator.c */
void	validate_map(const char *map_string, t_map *map_data);

/* error */
/* color_resolution_validator.c */
void	validate_resolution(char **line, t_game_elements *elements);
void	validate_floor_color(char **line, t_game_elements *elements);
void	validate_ceiling_color(char **line, t_game_elements *elements);

/* map_integrity_checker.c */
void	create_map_from_string(const char *map_string, t_map *map_data);

/* map_boundary_validator.c */
void	validate_map_space(int position, int count_x, const char **line, t_map *map_data);
void	validate_map_other(int position, int count_x, const char **line, t_map *map_data);
void	validate_map_wall(int position, int count_x, const char **line, t_map *map_data);

/* texture_file_validator.c */
void	validate_north_texture(char **line, t_game_elements *elements);
void	validate_south_texture(char **line, t_game_elements *elements);
void	validate_west_texture(char **line, t_game_elements *elements);
void	validate_east_texture(char **line, t_game_elements *elements);
void	validate_sprite_texture(char **line, t_game_elements *elements);

/* error_handler.c */
void	check_map_elements(const char *map_string, t_game_elements *elements);

/* core */
/* cub3d_core.c */
void	initialize_game(t_game_elements *elements, t_map *map_data);

/* sprite_finder.c */
void	locate_sprites(t_game_data *game_data, t_map *map_data);
void	sort_sprites_by_distance(double *order, double *distance, int total_sprites);

/* key_press_handler.c */
int		handle_key_press(int keycode, t_game_data *game_data);
int		handle_key_release(int keycode, t_game_data *game_data);

/* direction_setter.c */
void	set_initial_direction(char direction, t_game_data *game_data);

/* texel_handler.c */
void	draw_ceiling_and_floor(int x, int **buffer, t_game_data *game_data);
void	calculate_wall_texture_x(t_game_data *game_data);
void	calculate_texture_position(t_game_data *game_data);
void	draw_textured_wall(int x, int **buffer, t_game_data *game_data);

/* utils */
/*err_utils.c */
void	validate_texture_path(char *path);
int     parse_color_string(int *red, int *green, const char *color_string);

/* utils.c */
void	put_pixel_to_image(t_game_data *game_data, int x, int y, int color);
bool	initialize_frame_buffer(int mode, int ***buffer, t_game_data *game_data);
void	draw_frame_buffer(int **buffer, t_game_data *game_data);
void	draw_sprite_buffer(int width, int height, int **buffer, t_game_data *game_data);

/* main.c */
void	handle_error(const char *error_message);

#endif