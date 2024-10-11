#include "../../includes/cub3d.h"

void	move_player_forward(double move_speed, t_game_data *game_data)
{
	if (game_data->map.world[(int)game_data->player.pos_y]
		[(int)(game_data->player.pos_x + game_data->player.dir_x * move_speed)] == '0')
		game_data->player.pos_x += game_data->player.dir_x * move_speed;
	if (game_data->map.world[(int)(game_data->player.pos_y + game_data->player.dir_y * move_speed)]
		[(int)game_data->player.pos_x] == '0')
		game_data->player.pos_y += game_data->player.dir_y * move_speed;
}

void	move_player_backward(double move_speed, t_game_data *game_data)
{
	if (game_data->map.world[(int)game_data->player.pos_y]
		[(int)(game_data->player.pos_x - game_data->player.dir_x * move_speed)] == '0')
		game_data->player.pos_x -= game_data->player.dir_x * move_speed;
	if (game_data->map.world[(int)(game_data->player.pos_y - game_data->player.dir_y * move_speed)]
		[(int)game_data->player.pos_x] == '0')
		game_data->player.pos_y -= game_data->player.dir_y * move_speed;
}

void	move_player_left(double move_speed, t_game_data *game_data)
{
	double lateral_dir_x;
	double lateral_dir_y;

	lateral_dir_x = -game_data->player.dir_y;
	lateral_dir_y = game_data->player.dir_x;
	if (game_data->map.world[(int)game_data->player.pos_y]
		[(int)(game_data->player.pos_x + lateral_dir_x * move_speed)] == '0')
		game_data->player.pos_x += lateral_dir_x * move_speed;
	if (game_data->map.world[(int)(game_data->player.pos_y + lateral_dir_y * move_speed)]
		[(int)game_data->player.pos_x] == '0')
		game_data->player.pos_y += lateral_dir_y * move_speed;
}

void	move_player_right(double move_speed, t_game_data *game_data)
{
	double lateral_dir_x;
	double lateral_dir_y;

	lateral_dir_x = game_data->player.dir_y;
	lateral_dir_y = -game_data->player.dir_x;
	if (game_data->map.world[(int)game_data->player.pos_y]
		[(int)(game_data->player.pos_x + lateral_dir_x * move_speed)] == '0')
		game_data->player.pos_x += lateral_dir_x * move_speed;
	if (game_data->map.world[(int)(game_data->player.pos_y + lateral_dir_y * move_speed)]
		[(int)game_data->player.pos_x] == '0')
		game_data->player.pos_y += lateral_dir_y * move_speed;
}

void	update_player_position(t_game_data *game_data)
{
	double	move_speed;
	double	rotation_speed;

	move_speed = 0.1;
	rotation_speed = -0.05;
	if (game_data->key.move_up == 1)
		move_player_forward(move_speed, game_data);
	if (game_data->key.move_down == 1)
		move_player_backward(move_speed, game_data);
	if (game_data->key.move_left == 1)
		move_player_left(move_speed, game_data);
	if (game_data->key.move_right == 1)
		move_player_right(move_speed, game_data);
	if (game_data->key.rotate_right == 1)
		rotate_player_right(rotation_speed, game_data);
	if (game_data->key.rotate_left == 1)
		rotate_player_left(rotation_speed, game_data);
}
