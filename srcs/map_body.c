#include "../includes/cub3d.h"

void	map_space(int pos, int count_x, char **line, t_map_data *map_data)
{
	if ((map_data->matrix[pos][count_x - 1] != 'x'
		&& map_data->matrix[pos][count_x - 1] != '1')
		|| (map_data->matrix[pos - 1][count_x] != 'x'
		&& map_data->matrix[pos - 1][count_x] != '1'))
		ft_error("Error:\n");
	printf("--%c--", map_data->matrix[pos - 1][count_x]);
	if ((*line)[count_x] == '1')
		map_data->matrix[pos][count_x] = '1';
}

void	map_other(int pos, int count_x, char **line, t_map_data *map_data)
{
	if (map_data->matrix[pos][count_x - 1] == 'x'
			|| map_data->matrix[pos - 1][count_x] == 'x')
		ft_error("Error:\n");
	map_data->matrix[pos][count_x] = (*line)[count_x];
}

void	map_x(int pos, int count_x, char **line, t_map_data *map_data)
{
	while (map_data->matrix[pos][count_x])
	{
		map_space(pos, count_x, line, map_data);
		count_x++;
	}
}
