#include "../../includes/cub3d.h"

static void	swap_sprite_values(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	initialize_sprite_positions(t_game_data *game_data, t_map *map_data)
{
	int	i;
	int	j;
	int	sprite_count;

	i = 0;
	sprite_count = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width)
		{
			if (game_data->map.world[i][j] == '2')
			{
				game_data->sprite.buffer[sprite_count] = (double *)malloc(sizeof(double) * 2);
				if (!game_data->sprite.buffer[sprite_count])
					return ;
				game_data->sprite.buffer[sprite_count][0] = i + 0.5;
				game_data->sprite.buffer[sprite_count][1] = j + 0.5;
				sprite_count++;
			}
			j++;
		}
		i++;
	}
}

void	locate_sprites(t_game_data *game_data, t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	game_data->sprite.total = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width)
		{
			if (game_data->map.world[i][j] == '2')
				game_data->sprite.total++;
			j++;
		}
		i++;
	}
	game_data->sprite.z_buffer = (double *)malloc(sizeof(double) * game_data->screen_width);
	game_data->sprite.distance = (double *)malloc(sizeof(double) * game_data->sprite.total);
	game_data->sprite.buffer = (double **)malloc(sizeof(double *) * game_data->sprite.total);
	game_data->sprite.order = (double *)malloc(sizeof(double) * game_data->sprite.total);
	if (!game_data->sprite.z_buffer || !game_data->sprite.distance || 
		!game_data->sprite.buffer || !game_data->sprite.order)
		return ;
	initialize_sprite_positions(game_data, map_data);
}

void	sort_sprites_by_distance(double *order, double *distance, int total_sprites)
{
	int		i;
	int		j;
	int		max_index;
	double	max_distance;

	i = 0;
	while (i < total_sprites)
	{
		j = i + 1;
		max_index = i;
		max_distance = distance[i];
		while (j < total_sprites)
		{
			if (distance[j] > max_distance)
			{
				max_distance = distance[j];
				max_index = j;
			}
			j++;
		}
		if (max_index != i)
		{
			swap_sprite_values(&order[i], &order[max_index]);
			swap_sprite_values(&distance[i], &distance[max_index]);
		}
		i++;
	}
}
