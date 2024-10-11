#include "../../includes/cub3d.h"

void	rotate_player_right(double rotation_speed, t_game_data *game_data)
{
	double	old_direction_x;
	double	old_plane_x;
	double	temp;

	old_direction_x = game_data->player.dir_x;
	game_data->player.dir_x = game_data->player.dir_x * cos(-rotation_speed) - game_data->player.dir_y * sin(-rotation_speed);
	game_data->player.dir_y = old_direction_x * sin(-rotation_speed) + game_data->player.dir_y * cos(-rotation_speed);
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	old_plane_x = game_data->player.plane_x;
	game_data->player.plane_x = game_data->player.plane_x * cos(-rotation_speed) - game_data->player.plane_y * sin(-rotation_speed);
	game_data->player.plane_y = old_plane_x * sin(-rotation_speed) + game_data->player.plane_y * cos(-rotation_speed);
}

void	rotate_player_left(double rotation_speed, t_game_data *game_data)
{
	double	old_direction_x;
	double	old_plane_x;
	double	temp;

	old_direction_x = game_data->player.dir_x;
	game_data->player.dir_x = game_data->player.dir_x * cos(rotation_speed) - game_data->player.dir_y * sin(rotation_speed);
	game_data->player.dir_y = old_direction_x * sin(rotation_speed) + game_data->player.dir_y * cos(rotation_speed);
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	old_plane_x = game_data->player.plane_x;
	game_data->player.plane_x = game_data->player.plane_x * cos(rotation_speed) - game_data->player.plane_y * sin(rotation_speed);
	game_data->player.plane_y = old_plane_x * sin(rotation_speed) + game_data->player.plane_y * cos(rotation_speed);
}
