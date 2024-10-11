#include "../../includes/cub3d.h"

static void	determine_texture_color(int texture_y, char **color, t_game_data *game_data)
{
	if (game_data->map.side == 0 && game_data->ray.dir_x > 0)
	{
		texture_y = (int)game_data->texture.tex_pos & (game_data->east.height - 1);
		(*color) = game_data->east.addr + (texture_y * game_data->east.line_length);
		(*color) += (game_data->texture.tex_x * (game_data->east.bits_per_pixel / 8));
	}
	else if (game_data->map.side == 0 && game_data->ray.dir_x < 0)
	{
		texture_y = (int)game_data->texture.tex_pos & (game_data->west.height - 1);
		(*color) = game_data->west.addr + (texture_y * game_data->west.line_length);
		(*color) += (game_data->texture.tex_x * (game_data->west.bits_per_pixel / 8));
	}
	else if (game_data->map.side == 1 && game_data->ray.dir_y > 0)
	{
		texture_y = (int)game_data->texture.tex_pos & (game_data->south.height - 1);
		(*color) = game_data->south.addr + (texture_y * game_data->south.line_length);
		(*color) += (game_data->texture.tex_x * (game_data->south.bits_per_pixel / 8));
	}
	else
	{
		texture_y = (int)game_data->texture.tex_pos & (game_data->north.height - 1);
		(*color) = game_data->north.addr + (texture_y * game_data->north.line_length);
		(*color) += (game_data->texture.tex_x * (game_data->north.bits_per_pixel / 8));
	}
}

void	draw_ceiling_and_floor(int x, int **buffer, t_game_data *game_data)
{
	int	i;

	i = 0;
	while (i < game_data->screen_height)
	{
		if (i < game_data->sprite.start_y)
			buffer[i][x] = game_data->map.ceiling_color;
		else if (i >= game_data->sprite.end_y)
			buffer[i][x] = game_data->map.floor_color;
		i++;
	}
}

void	calculate_wall_texture_x(t_game_data *game_data)
{
	int	texture_position;

	if (game_data->map.side == 0)
		game_data->texture.wall_x = game_data->player.pos_y + game_data->ray.wall_dist * game_data->ray.dir_y;
	else
		game_data->texture.wall_x = game_data->player.pos_x + game_data->ray.wall_dist * game_data->ray.dir_x;
	game_data->texture.wall_x -= floor(game_data->texture.wall_x);
	if (game_data->map.side == 0 && game_data->ray.dir_x >= 0)
	{
		texture_position = (int)(game_data->texture.wall_x * (double)game_data->east.width);
		texture_position = game_data->east.width - texture_position - 1;
	}
	else if (game_data->map.side == 0 && game_data->ray.dir_x < 0)
		texture_position = (int)(game_data->texture.wall_x * (double)game_data->west.width);
	else if (game_data->map.side == 1 && game_data->ray.dir_y >= 0)
		texture_position = (int)(game_data->texture.wall_x * (double)game_data->south.width);
	else
	{
		texture_position = (int)(game_data->texture.wall_x * (double)game_data->north.width);
		texture_position = game_data->north.width - texture_position - 1;
	}
	game_data->texture.tex_x = texture_position;
}

void	calculate_texture_position(t_game_data *game_data)
{
	double	step;
	double	texture_position;

	if (game_data->map.side == 0 && game_data->ray.dir_x >= 0)
		step = 1.0 * game_data->east.height / game_data->ray.line_height;
	else if (game_data->map.side == 0 && game_data->ray.dir_x < 0)
		step = 1.0 * game_data->west.height / game_data->ray.line_height;
	else if (game_data->map.side == 1 && game_data->ray.dir_y >= 0)
		step = 1.0 * game_data->south.height / game_data->ray.line_height;
	else
		step = 1.0 * game_data->north.height / game_data->ray.line_height;
	texture_position = (game_data->sprite.start_y - game_data->screen_height / 2 + game_data->ray.line_height / 2) * step;
	game_data->texture.step = step;
	game_data->texture.tex_pos = texture_position;
}

void	draw_textured_wall(int x, int **buffer, t_game_data *game_data)
{
	char	*color;
	int		texture_y;
	int		y;

	color = NULL;
	y = game_data->sprite.start_y;
	while (y < game_data->sprite.end_y)
	{
		texture_y = 0;
		determine_texture_color(texture_y, &color, game_data);
		buffer[y][x] = *(unsigned int *)color;
		game_data->texture.tex_pos += game_data->texture.step;
		y++;
	}
}
