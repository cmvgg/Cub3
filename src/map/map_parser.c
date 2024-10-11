#include "../../includes/cub3d.h"

static void	validate_map_line(int row, char **line, t_map *map_data)
{
	int	col;

	col = 1;
	while ((*line)[col])
	{
		if ((*line)[col] == '1')
			map_data->grid[row][col] = '1';
		else if ((*line)[col] == ' ')
			validate_map_space(row, col, (const char **)line, map_data);
		else
		{
			if ((*line)[col] != '0' && (*line)[col] != '2' && (*line)[col] != '1')
			{
				write(1, "X", 1);
				map_data->player_count++;
			}
			if (map_data->player_count > 2)
				handle_error("Error\nThe map contains more than one player");
			validate_map_other(row, col, (const char **)line, map_data);
		}
		col++;
	}
	if ((*line)[col] == '\0' && col < map_data->width)
		validate_map_wall(row, col, (const char **)line, map_data);
}

static void	validate_line(int row, char **line, t_map *map_data)
{
	int	col;
	int	last_col;

	col = 0;
	last_col = 0;
	if ((*line)[col] != '1' && (*line)[col] != ' ' && (*line)[col] != '\0')
		handle_error("Error\nThe map is not properly enclosed");
	if ((*line)[col] == '1')
		map_data->grid[row][col] = '1';
	last_col = ft_strlen(*line) - 1;
	if ((*line)[last_col] != '1' && (*line)[last_col] != ' ' && (*line)[col] != '\0')
		handle_error("Error\nThe map is not properly enclosed");
	validate_map_line(row, line, map_data);
}

void	parse_map_first_line(char **line, t_map *map_data)
{
	int	col;

	col = 0;
	while ((*line)[col] && map_data->grid[0][col])
	{
		
		if ((*line)[col] != '1' && (*line)[col] != ' ')
			handle_error("Error\nThe map is not properly enclosed");
		if ((*line)[col] == '1')
			map_data->grid[0][col] = '1';
		col++;
	}
	free(*line);
}

void	parse_map_body(int fd, char **line, t_map *map_data)
{
	int	read_status;
	int	row;

	read_status = 1;
	row = 1;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, line);
		if (row == map_data->height - 1)
			break;
		validate_line(row, line, map_data);
		free(*line);
		row++;
	}
}

void	parse_map_last_line(char **line, t_map *map_data)
{
	int	row;
	int	col;

	row = map_data->height - 1;
	col = 0;
	while ((*line)[col] && map_data->grid[row][col])
	{
		if ((*line)[col] != '1' && (*line)[col] != ' ')
			handle_error("Error\nThe map is not properly enclosed");
		col++;
	}
	validate_line(row, line, map_data);
	free(*line);
}
