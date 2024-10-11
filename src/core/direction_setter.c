#include "../../includes/cub3d.h"

static void	set_north_direction(t_game_data *game_data)
{
	double	temp;

	game_data->player.dir_x = 0;
	game_data->player.dir_y = -1;
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	game_data->player.plane_x = 0.66;
	game_data->player.plane_y = 0;
}

static void	set_south_direction(t_game_data *game_data)
{
	double	temp;

	game_data->player.dir_x = 0;
	game_data->player.dir_y = 1;
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	game_data->player.plane_x = -0.66;
	game_data->player.plane_y = 0;
}

static void	set_east_direction(t_game_data *game_data)
{
	double	temp;

	game_data->player.dir_x = 1;
	game_data->player.dir_y = 0;
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	game_data->player.plane_x = 0;
	game_data->player.plane_y = 0.66;
}

static void	set_west_direction(t_game_data *game_data)
{
	double	temp;

	game_data->player.dir_x = -1;
	game_data->player.dir_y = 0;
	temp = game_data->player.dir_x;
	game_data->player.plane_x = game_data->player.dir_y;
	game_data->player.plane_y = -temp;
	game_data->player.plane_x = 0;
	game_data->player.plane_y = -0.66;
}

void	set_initial_direction(char direction, t_game_data *game_data)
{
	if (direction == 'N')
		set_north_direction(game_data);
	else if (direction == 'S')
		set_south_direction(game_data);
	else if (direction == 'W')
		set_west_direction(game_data);
	else if (direction == 'E')
		set_east_direction(game_data);
	else
	{
		/* Error
		   Invalid direction character. The direction must be 'N', 'S', 'E', or 'W'. */
		handle_error("Invalid direction character in map.");
	}
}
