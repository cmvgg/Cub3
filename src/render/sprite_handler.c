#include "../../includes/cub3d.h"

static void	calculate_sprite_distances(t_game_data *game_data)
{
	int	sprite_index;

	sprite_index = 0;
	while (sprite_index < game_data->sprite.total)
	{
		game_data->sprite.order[sprite_index] = (double)sprite_index;
		game_data->sprite.distance[sprite_index] = pow(game_data->player.pos_x - game_data->sprite.buffer[sprite_index][1], 2);
		game_data->sprite.distance[sprite_index] += pow(game_data->player.pos_y - game_data->sprite.buffer[sprite_index][0], 2);
		sprite_index++;
	}
	sort_sprites_by_distance(game_data->sprite.order, game_data->sprite.distance, game_data->sprite.total);
}

static void	calculate_sprite_projection(int sprite_index, t_game_data *game_data)
{
	double	inverse_determinant;

	game_data->sprite.pos_x = game_data->sprite.buffer[(int)game_data->sprite.order[sprite_index]][1] - game_data->player.pos_x;
	game_data->sprite.pos_y = game_data->sprite.buffer[(int)game_data->sprite.order[sprite_index]][0] - game_data->player.pos_y;
	inverse_determinant = 1.0 / (game_data->player.plane_x * game_data->player.dir_y - game_data->player.dir_x * game_data->player.plane_y);
	game_data->sprite.dir_x = (game_data->player.dir_y * game_data->sprite.pos_x - game_data->player.dir_x * game_data->sprite.pos_y);
	game_data->sprite.dir_x *= inverse_determinant;
	game_data->sprite.dir_y = (-game_data->player.plane_y * game_data->sprite.pos_x + game_data->player.plane_x * game_data->sprite.pos_y);
	game_data->sprite.dir_y *= inverse_determinant;
}

static void	calculate_sprite_height(int *sprite_height, t_game_data *game_data)
{
	*sprite_height = abs((int)(game_data->screen_height / game_data->sprite.dir_y));
	game_data->sprite.start_y = game_data->screen_height / 2 - *sprite_height / 2;
	if (game_data->sprite.start_y < 0)
		game_data->sprite.start_y = 0;
	game_data->sprite.end_y = game_data->screen_height / 2 + *sprite_height / 2;
	if (game_data->sprite.end_y >= game_data->screen_height)
		game_data->sprite.end_y = game_data->screen_height - 1;
}

static void	calculate_sprite_width(int *sprite_width, t_game_data *game_data)
{
	game_data->sprite.screen_x = (int)((game_data->screen_width / 2) * (1 + game_data->sprite.dir_x / game_data->sprite.dir_y));
	*sprite_width = abs((int)(game_data->screen_height / game_data->sprite.dir_y));
	game_data->sprite.start_x = game_data->sprite.screen_x - *sprite_width / 2;
	if (game_data->sprite.start_x < 0)
		game_data->sprite.start_x = 0;
	game_data->sprite.end_x = game_data->sprite.screen_x + *sprite_width / 2;
	if (game_data->sprite.end_x >= game_data->screen_width)
		game_data->sprite.end_x = game_data->screen_width - 1;
}

void	render_sprites(int **buffer, t_game_data *game_data)
{
	int	sprite_index;
	int	sprite_height;
	int	sprite_width;

	calculate_sprite_distances(game_data);
	sprite_index = 0;
	while (sprite_index < game_data->sprite.total)
	{
		calculate_sprite_projection(sprite_index, game_data);
		calculate_sprite_height(&sprite_height, game_data);
		calculate_sprite_width(&sprite_width, game_data);
		draw_sprite_buffer(sprite_width, sprite_height, buffer, game_data);
		sprite_index++;
	}
}
