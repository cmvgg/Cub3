#include "../../includes/cub3d.h"

void	validate_map_space(int row, int col, const char **line, t_map *map_data)
{
	if ((map_data->grid[row][col - 1] != 'x'
		&& map_data->grid[row][col - 1] != '1')
		|| (map_data->grid[row - 1][col] != 'x'
		&& map_data->grid[row - 1][col] != '1'))
		handle_error("Error\nSpaces must be surrounded by walls");
	if ((*line)[col] == '1')
		map_data->grid[row][col] = '1';
}

void	validate_map_other(int row, int col, const char **line, t_map *map_data)
{
	if (map_data->grid[row][col - 1] == 'x'
			|| map_data->grid[row - 1][col] == 'x')
		handle_error("Error\nSpaces must be surrounded by walls");
	map_data->grid[row][col] = (*line)[col];
}

void	validate_map_wall(int row, int col, const char **line, t_map *map_data)
{
	while (map_data->grid[row][col])
	{
		validate_map_space(row, col, line, map_data);
		col++;
	}
}

void	validate_map(const char *map_string, t_map *map_data)
{
	int		row;
	int		col;

	row = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->grid[row][col] == ' ')
				validate_map_space(row, col, &map_string, map_data);
			else if (map_data->grid[row][col] == '0' || map_data->grid[row][col] == '2'
					|| map_data->grid[row][col] == 'N' || map_data->grid[row][col] == 'S'
					|| map_data->grid[row][col] == 'E' || map_data->grid[row][col] == 'W')
				validate_map_other(row, col, &map_string, map_data);
			col++;
		}
		row++;
	}
}
