#include "../../includes/cub3d.h"

static void	load_texture(const char *path, t_texture *texture, void *mlx_ptr)
{
	char *path_copy;

	path_copy = ft_strdup(path);
	if (!path_copy)
	{
		/* Error
		Failed to allocate memory for path copy */
		handle_error("Memory allocation failed");
	}

	texture->img = mlx_xpm_file_to_image(mlx_ptr, path_copy, &texture->width, &texture->height);
	if (texture->img == NULL)
	{
		/* Error
		Failed to load texture image */
		free(path_copy);
		handle_error("Failed to load texture image");
	}

	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		/* Error
		Failed to get texture data address */
		mlx_destroy_image(mlx_ptr, texture->img);
		free(path_copy);
		handle_error("Failed to get texture data address");
	}

	free(path_copy);
}

void	load_north_texture(t_game_data *game_data)
{
	load_texture(game_data->north.path, &game_data->north, game_data->mlx.mlx);
}

void	load_south_texture(t_game_data *game_data)
{
	load_texture(game_data->south.path, &game_data->south, game_data->mlx.mlx);
}

void	load_east_texture(t_game_data *game_data)
{
	load_texture(game_data->east.path, &game_data->east, game_data->mlx.mlx);
}

void	load_west_texture(t_game_data *game_data)
{
	load_texture(game_data->west.path, &game_data->west, game_data->mlx.mlx);
}

void	load_sprite_texture(t_game_data *game_data)
{
	load_texture(game_data->sprite.texture.path, &game_data->sprite.texture, game_data->mlx.mlx);
}
