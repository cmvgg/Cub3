/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/24 21:07:15 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_body_line(int pos, char **line, t_map_data *map_data)
{
	int	count_x;

	count_x = 1;
	while ((*line)[count_x] != 0 && count_x < map_data->width)
	{
		if ((*line)[count_x] == '1')
			map_data->matrix[pos][count_x] = '1';
		else if ((*line)[count_x] == ' ')
			map_space(pos, count_x, map_data, line);
		else
		{
			if ((*line)[count_x] != '0' && (*line)[count_x] != '2'
				&& (*line)[count_x] != '1')
			{
				map_data->player++;
			}
			if (map_data->player >= 2)
				ft_error("Error:cbl\n", *line);
			map_other(pos, count_x, line, map_data);
		}
		count_x++;
	}
	if ((*line)[count_x] == '\0' && count_x < map_data->width)
		map_x(pos, count_x, map_data, line);
}

static void	check_line(int pos, char **line, t_map_data *map_data)
{
	int	count_x;
	int	last;

	count_x = 0;
	if ((*line)[count_x] != '1' && (*line)[count_x] != ' ')
		ft_error("Error:cl\n", *line);
	if ((*line)[count_x] == '1')
		map_data->matrix[pos][count_x] = '1';
	last = ft_strlen(*line) - 1;
	if ((*line)[last] != '1' && (*line)[last] != ' ')
		ft_error("Error:cl1\n", *line);
	check_body_line(pos, line, map_data);
}

void	validate_map_first_line(char **line, t_map_data *map_data)
{
	int	count_x;

	count_x = 0;
	while ((*line)[count_x] && map_data->matrix[0][count_x])
	{
		if ((*line)[count_x] != '1' && (*line)[count_x] != ' ')
			ft_error("Error:vmfl\n", *line);
		if ((*line)[count_x] == '1')
			map_data->matrix[0][count_x] = '1';
		count_x++;
	}
}

void	validate_map_lines(int fd, char **line, t_map_data *map_data)
{
	int	reads;
	int	pos;

	reads = 1;
	pos = 1;
	free(*line);
	while (reads >= 1)
	{
		reads = get_next_line(fd, line);
		if (pos == map_data->height - 1 || reads <= 0)
			break ;
		check_line(pos, line, map_data);
		if (pos == map_data->height - 2 || reads <= 0)
			break ;
		free(line[0]);
		pos++;
	}
}

void	validate_map_last_line(char *line, t_map_data *map_data)
{
	int	pos;
	int	count_x;

	pos = map_data->height - 1;
	count_x = 0;
	while ((line)[count_x] != 0 && map_data->matrix[pos][count_x])
	{
		if ((line)[count_x] == '\0')
			break ;
		if ((line)[count_x] != '1' && (line)[count_x] != ' ')
		{
			ft_error("Error:vmll\n", line);
		}
		count_x++;
	}
}
