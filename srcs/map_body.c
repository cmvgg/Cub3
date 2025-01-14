/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_body.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:53:03 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/14 14:59:17 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_space(int pos, int count_x, char **line, t_map_data *map_data)
{
	if (count_x < 0 || count_x >= map_data->width)
		ft_error("Error: Invalid access in map_space\n");
	if (pos > 0 && count_x > 0)
	{
		if ((map_data->matrix[pos][count_x - 1] != 'x'
			&& map_data->matrix[pos][count_x - 1] != '1')
			|| (map_data->matrix[pos - 1][count_x] != 'x'
				&& map_data->matrix[pos - 1][count_x] != '1'))
		{
			ft_error("Error: Invalid map structure\n");
		}
	}
	if ((*line)[count_x] == '1')
		map_data->matrix[pos][count_x] = '1';
}

void	map_other(int pos, int count_x, char **line, t_map_data *map_data)
{
	if (map_data->matrix[pos][count_x - 1] == 'x' || map_data->matrix[pos
		- 1][count_x] == 'x')
		ft_error("Error:e1\n");
	map_data->matrix[pos][count_x] = (*line)[count_x];
}

void	map_x(int pos, int count_x, char **line, t_map_data *map_data)
{
	while ((count_x) < map_data->width && map_data->matrix[pos][count_x])
	{
		map_space(pos, count_x, line, map_data);
		count_x++;
	}
}
