/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:21 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/02 23:30:23 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_values(int read_stat, char *line_cont,
		t_map_data *map_data)
{
	int	index;

	index = 0;
	while (line_cont[index])
	{
		if (line_cont[index] == '\t' || line_cont[index] == '\n'
			|| line_cont[index] == '\f' || line_cont[index] == '\v'
			|| line_cont[index] == '\r')
		{
			ft_error("Error:1\n");
		}
		if (read_stat == -1 || (line_cont[index] != '0'
				&& line_cont[index] != '1' && line_cont[index] != '2'
				&& line_cont[index] != ' ' && line_cont[index] != 'N'
				&& line_cont[index] != 'S' && line_cont[index] != 'E'
				&& line_cont[index] != 'W'))
		{
			ft_error("Error:2\n");
		}
		if ((int)ft_strlen(line_cont) > map_data->width)
			map_data->width = ft_strlen(line_cont);
		index++;
	}
	map_data->height++;
	return (read_stat);
}

static void	elem_texture_to_map(int fd, t_map_data *map_data)
{
	char	*current_line;
	int		read_status;

	read_status = 1;
	map_data->width = 0;
	map_data->height = 0;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, &current_line);
		if (*current_line != '\0')
			break ;
		if (read_status == -1 || read_status == 0)
		{
			ft_error("Error:3\n");
		}
		free(current_line);
	}
	check_map_values(read_status, current_line, map_data);
	free(current_line);
}

void	check_validate_map(const char *map_use, t_map_data *map_data)
{
	char	*current_line;
	int		read_count;
	int		fd;

	read_count = 0;
	fd = open(map_use, O_RDONLY);
	while (1)
	{
		get_next_line(fd, &current_line);
		if (*current_line == '\0')
			break;
		free(current_line);
	}
	elem_texture_to_map(fd, map_data);
	read_count = 1;
	while (read_count == 1)
	{
		read_count = get_next_line(fd, &current_line);
		read_count = check_map_values(read_count, current_line, map_data);
		free(current_line);
	}
	close(fd);
}
