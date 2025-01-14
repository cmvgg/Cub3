/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/14 16:13:38 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_body_line(int pos, char **line, t_map_data *map_data)
{
	int	count_x;

	count_x = 1;
	printf("\n\nline: %s\n\n", *line);
	while ((*line)[count_x] != 0 && count_x < map_data->width)
	{
		if ((*line)[count_x] == '1')
		{	
			map_data->matrix[pos][count_x] = '1';
			printf("\n\n%s\n\n", map_data->matrix[map_data->height - 1]); /*el error se produce aquí*/}
		else if ((*line)[count_x] == ' ')
			map_space(pos, count_x, line, map_data);
		else
		{
			if ((*line)[count_x] != '0' && (*line)[count_x] != '2'
				&& (*line)[count_x] != '1')
			{
				map_data->player++;
			}
			if (map_data->player > 2)
				ft_error("Error:cbl\n");
			map_other(pos, count_x, line, map_data);
		}
		count_x++;
	}
	if ((*line)[count_x] == '\0' && count_x < map_data->width)
		map_x(pos, count_x, line, map_data);
}

static void	check_line(int pos, char **line, t_map_data *map_data)
{
	int	count_x;
	int	last;

	count_x = 0;
	if ((*line)[count_x] != '1' && (*line)[count_x] != ' '
		&& (*line)[count_x] != '\0')
		ft_error("Error:cl\n");
	if ((*line)[count_x] == '1')
		map_data->matrix[pos][count_x] = '1';
	last = ft_strlen(*line) - 1;
	if ((*line)[last] != '1' && (*line)[last] != ' '
		&& (*line)[count_x] != '\0')
		ft_error("Error:cl1\n");
	check_body_line(pos, line, map_data);
}

void	validate_map_first_line(char **line, t_map_data *map_data)
{
	int	count_x;

	count_x = 0;
	while ((*line)[count_x] && map_data->matrix[0][count_x])
	{
		if ((*line)[count_x] != '1' && (*line)[count_x] != ' ')
			ft_error("Error:vmfl\n");
		if ((*line)[count_x] == '1')
			map_data->matrix[0][count_x] = '1';
		count_x++;
	}
}

void	validate_map_lines(int fd, char *line, t_map_data *map_data)
{
	int	reads;
	int	pos;

	reads = 1;
	pos = 1;
	while (reads >= 1)
	{
		reads = get_next_line(fd, &line);
		if (pos == map_data->height - 1)
			break ;
		if (reads)
			check_line(pos, &line, map_data);
		pos++;
	}
}

void	validate_map_last_line(char **line, t_map_data *map_data)
{
	int	pos;
	int	count_x;

	pos = map_data->height - 1;
	count_x = 0;
	while ((*line)[count_x] && map_data->matrix[pos][count_x])
	{
		if ((*line)[count_x] == '\0')
			break ;
		if ((*line)[count_x] != '1' && (*line)[count_x] != 'x')
			ft_error("Error:vmll\n");
		count_x++;
	}
	printf("line vmll: %s\n\n", *line);
	//check_line(pos, line, map_data);
}