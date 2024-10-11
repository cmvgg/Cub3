#include "../../includes/cub3d.h"

void	put_pixel_to_image(t_game_data *game_data, int x, int y, int color)
{
	char	*dst;

	dst = game_data->mlx.addr + (y * game_data->mlx.line_length) + (x * (game_data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

bool	initialize_frame_buffer(int mode, int ***buffer, t_game_data *game_data)
{
	int i;

	if (mode == 1)
	{
		*buffer = (int **)malloc(sizeof(int *) * game_data->screen_height);
		if (!(*buffer))
		{
			handle_error("Memory allocation failed for frame buffer");
			return (0);
		}
		
		i = 0;
		while (i < game_data->screen_height)
		{
			(*buffer)[i] = (int *)malloc(sizeof(int) * game_data->screen_width);
			if (!(*buffer)[i])
			{
				handle_error("Memory allocation failed for frame buffer row");
				return (0);
			}
			i++;
		}
	}
	else if (mode == 0)
	{
		i = 0;
		while (i < game_data->screen_height)
		{
			free((*buffer)[i]);
			i++;
		}
		free(*buffer);		
	}
	return (1);
}

void	draw_frame_buffer(int **buffer, t_game_data *game_data)
{
	int row, col;

	row = 0;
	while (row < game_data->screen_height)
	{
		col = 0;
		while (col < game_data->screen_width)
		{
			put_pixel_to_image(game_data, col, row, buffer[row][col]);
			col++;
		}
		row++;
	}
}

static int	calculate_texture_coordinate(int mode, int coordinate, int size, t_game_data *game_data)
{
	if (mode == 0)
	{
		return (int)((coordinate - (-size / 2 + game_data->sprite.screen_x)) * game_data->sprite.texture.width / size);
	}
	else if (mode == 1)
	{
		int d = coordinate * 256 - game_data->screen_height * 128 + size * 128;
		return ((d * game_data->sprite.texture.height) / size) / 256;
	}
	return (-1);
}

void	draw_sprite_buffer(int width, int height, int **buffer, t_game_data *game_data)
{
	int stripe, tex_x, tex_y, y;
	char *color;

	stripe = game_data->sprite.start_x;
	while (stripe < game_data->sprite.end_x)
	{
		tex_x = calculate_texture_coordinate(0, stripe, width, game_data);
		if (game_data->sprite.dir_y > 0 && stripe > 0 && stripe < game_data->screen_width
			&& game_data->sprite.dir_y < game_data->sprite.z_buffer[stripe])
		{
			y = game_data->sprite.start_y;
			while (y < game_data->sprite.end_y)
			{
				tex_y = calculate_texture_coordinate(1, y, height, game_data);
				color = game_data->sprite.texture.addr + (tex_y * game_data->sprite.texture.line_length) + (tex_x * (game_data->sprite.texture.bits_per_pixel / 8));
				if ((*(unsigned int *)color & 0x00FFFFFF) != 0)
					buffer[y][stripe] = *(unsigned int *)color;
				y++;
			}
		}
		stripe++;
	}
}
