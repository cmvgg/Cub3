#include "../../includes/cub3d.h"

static void	calculate_ray(int screen_x, t_game_data *game_data)
{
	double	camera_x;

	camera_x = 2 * screen_x / (double)game_data->screen_width - 1;
	game_data->ray.dir_x = game_data->player.dir_x + game_data->player.plane_x * camera_x;
	game_data->ray.dir_y = game_data->player.dir_y + game_data->player.plane_y * camera_x;
	game_data->ray.delta_dist_x = fabs(1 / game_data->ray.dir_x);
	game_data->ray.delta_dist_y = fabs(1 / game_data->ray.dir_y);
}

static void	calculate_step_and_side_dist(t_game_data *game_data)
{
	game_data->map.map_x = (int)game_data->player.pos_x;
	game_data->map.map_y = (int)game_data->player.pos_y;

	if (game_data->ray.dir_x < 0)
	{
		game_data->ray.step_x = -1;
		game_data->ray.side_dist_x = (game_data->player.pos_x - game_data->map.map_x) * game_data->ray.delta_dist_x;
	}
	else
	{
		game_data->ray.step_x = 1;
		game_data->ray.side_dist_x = (game_data->map.map_x + 1.0 - game_data->player.pos_x) * game_data->ray.delta_dist_x;
	}
	if (game_data->ray.dir_y < 0)
	{
		game_data->ray.step_y = -1;
		game_data->ray.side_dist_y = (game_data->player.pos_y - game_data->map.map_y) * game_data->ray.delta_dist_y;
	}
	else
	{
		game_data->ray.step_y = 1;
		game_data->ray.side_dist_y = (game_data->map.map_y + 1.0 - game_data->player.pos_y) * game_data->ray.delta_dist_y;
	}
}

static void	perform_dda(t_game_data *game_data)
{
	int	wall_hit;

	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (game_data->ray.side_dist_x < game_data->ray.side_dist_y)
		{
			game_data->ray.side_dist_x += game_data->ray.delta_dist_x;
			game_data->map.map_x += game_data->ray.step_x;
			game_data->map.side = 0;
		}
		else
		{
			game_data->ray.side_dist_y += game_data->ray.delta_dist_y;
			game_data->map.map_y += game_data->ray.step_y;
			game_data->map.side = 1;
		}
		if (game_data->map.world[game_data->map.map_y][game_data->map.map_x] == '1')
			wall_hit = 1;
	}
}

static void	calculate_wall_height(int **buffer, int screen_x, t_game_data *game_data)
{
	if (game_data->map.side == 0)
		game_data->ray.wall_dist = (game_data->map.map_x - game_data->player.pos_x + (1 - game_data->ray.step_x) / 2) / game_data->ray.dir_x;
	else
		game_data->ray.wall_dist = (game_data->map.map_y - game_data->player.pos_y + (1 - game_data->ray.step_y) / 2) / game_data->ray.dir_y;

	game_data->ray.line_height = (int)(game_data->screen_height / game_data->ray.wall_dist);
	game_data->sprite.start_y = game_data->screen_height / 2 - game_data->ray.line_height / 2;
	if (game_data->sprite.start_y < 0)
		game_data->sprite.start_y = 0;
	game_data->sprite.end_y = game_data->screen_height / 2 + game_data->ray.line_height / 2;
	if (game_data->sprite.end_y >= game_data->screen_height)
		game_data->sprite.end_y = game_data->screen_height - 1;

	draw_ceiling_and_floor(screen_x, buffer, game_data);
	calculate_wall_texture_x(game_data);
	calculate_texture_position(game_data);
	draw_textured_wall(screen_x, buffer, game_data);
}

int	render_game_frame(t_game_data *game_data)
{
	int	screen_x;
	int	**buffer;

	screen_x = 0;
	if (!initialize_frame_buffer(1, &buffer, game_data))
		return (1);
	while (screen_x < game_data->screen_width)
	{
		calculate_ray(screen_x, game_data);
		calculate_step_and_side_dist(game_data);
		perform_dda(game_data);
		calculate_wall_height(buffer, screen_x, game_data);
		game_data->sprite.z_buffer[screen_x] = game_data->ray.wall_dist;
		screen_x++;
	}
	render_sprites(buffer, game_data);
	draw_frame_buffer(buffer, game_data);
	if (!initialize_frame_buffer(0, &buffer, game_data))
		return (1);
	mlx_put_image_to_window(game_data->mlx.mlx, game_data->mlx.window, game_data->mlx.img, 0, 0);
	mlx_do_sync(game_data->mlx.mlx);
	return (0);
}
