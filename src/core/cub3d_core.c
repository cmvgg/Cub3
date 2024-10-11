#include "../../includes/cub3d.h"

static int	exit_game(void)
{
	printf("\033[0;32mCub3D closed successfully :)\n\033[0;32");
	printf("\n");
	exit(0);
}

static void	find_player_position(t_game_data *game_data, t_map *map_data)
{
	int		row;
	int		col;
	char	*player_chars;
	int		i;

	player_chars = "NSEW";
	row = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			i = 0;
			while (player_chars[i])
			{
				if (map_data->grid[row][col] == player_chars[i])
				{
					set_initial_direction(map_data->grid[row][col], game_data);
					game_data->player.pos_x = (double)col + 0.2;
					game_data->player.pos_y = (double)row + 0.2;
					map_data->grid[row][col] = '0';
					return;
				}
				i++;
			}
			col++;
		}
		row++;
	}
	/* Error
	   No player position found in the map. The map must contain exactly one player position (N, S, E, or W). */
	handle_error("No player position found in the map.");
}

static void	initialize_game_values(t_game_data *game_data, t_game_elements *elements, t_map *map_data)
{
	int	ceiling_color;
	int	floor_color;

	game_data->map.world = map_data->grid;
	game_data->screen_width = elements->resolution.width;
	game_data->screen_height = elements->resolution.height;
	ceiling_color = (elements->color.ceiling_rgb[0] << 16) + 
					(elements->color.ceiling_rgb[1] << 8) + 
					elements->color.ceiling_rgb[2];
	floor_color = (elements->color.floor_rgb[0] << 16) + 
				  (elements->color.floor_rgb[1] << 8) + 
				  elements->color.floor_rgb[2];
	game_data->map.ceiling_color = ceiling_color;
	game_data->map.floor_color = floor_color;
	game_data->key.move_up = 0;
	game_data->key.move_down = 0;
	game_data->key.move_right = 0;
	game_data->key.move_left = 0;
	game_data->key.rotate_left = 0;
	game_data->key.rotate_right = 0;
	game_data->key.exit_game = 0;
}

static void	load_game_textures(t_game_data *game_data, t_game_elements *elements)
{
	game_data->north.path = ft_strtrim(elements->north.path, " \t");
	load_north_texture(game_data);
	game_data->south.path = ft_strtrim(elements->south.path, " \t");
	load_south_texture(game_data);
	game_data->east.path = ft_strtrim(elements->east.path, " \t");
	load_east_texture(game_data);
	game_data->west.path = ft_strtrim(elements->west.path, " \t");
	load_west_texture(game_data);
	game_data->sprite.texture.path = ft_strtrim(elements->sprite.texture.path, " \t");
	load_sprite_texture(game_data);
	game_data->mlx.window = mlx_new_window(game_data->mlx.mlx, 
		game_data->screen_width, game_data->screen_height, "Cub3D");
	game_data->mlx.img = mlx_new_image(game_data->mlx.mlx, 
		game_data->screen_width, game_data->screen_height);
	game_data->mlx.addr = mlx_get_data_addr(game_data->mlx.img,
		&game_data->mlx.bits_per_pixel, &game_data->mlx.line_length, 
		&game_data->mlx.endian);
}

void	initialize_game(t_game_elements *elements, t_map *map_data)
{
	t_game_data	game_data;
	int			max_screen_width;
	int			max_screen_height;

	game_data.mlx.mlx = mlx_init();
	if (!game_data.mlx.mlx)
	{
		/* Error
		   Failed to initialize MLX. Check if the necessary libraries are installed and linked correctly. */
		handle_error("Failed to initialize MLX.");
	}
	find_player_position(&game_data, map_data);
	initialize_game_values(&game_data, elements, map_data);
	load_game_textures(&game_data, elements);
	locate_sprites(&game_data, map_data);
	mlx_get_screen_size(game_data.mlx.mlx, &max_screen_width, &max_screen_height);
	game_data.screen_width = (game_data.screen_width > max_screen_width) ? 
		max_screen_width : game_data.screen_width;
	game_data.screen_height = (game_data.screen_height > max_screen_height) ? 
		max_screen_height : game_data.screen_height;
	mlx_hook(game_data.mlx.window, 2, 1L << 0, handle_key_press, &game_data);
	mlx_hook(game_data.mlx.window, 3, 1L << 1, handle_key_release, &game_data);
	mlx_hook(game_data.mlx.window, 17, 1L << 17, exit_game, &game_data);
	mlx_loop_hook(game_data.mlx.mlx, render_game_frame, &game_data);
	mlx_loop(game_data.mlx.mlx);
}
