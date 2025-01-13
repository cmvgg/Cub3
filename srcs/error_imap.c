/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_imap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:14 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/13 18:51:49 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	elem_texture_to_map(int fd, char **current_line)
{
	int		read_status;

	read_status = 1;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, current_line);
		if (**current_line != '\0')
			break ;
		free(*current_line);
	}
}

static void	check_values(const char *map_use, t_map_data *map_data)
{
	static char	*current_line;
	int			fd;

	fd = 0;
	fd = open(map_use, O_RDONLY);
	while (1)
	{
		get_next_line(fd, &current_line);
		if (*current_line == '\0')
			break ;
		free(current_line);
	}	
	free(current_line);
	elem_texture_to_map(fd, &current_line);
	map_data->player = 0;
	validate_map_first_line(&current_line, map_data);
	validate_map_lines(fd, current_line, map_data);
	if (map_data->player == 0)
		ft_error("Error: No player\n");
	validate_map_last_line(&current_line, map_data);
	close(fd);
}

void	create_map(const char *map_use, t_map_data *map_data)
{
	int	row_idx;
	int	column_idx;

	row_idx = 0;
	map_data->matrix
		= (char **)ft_calloc(sizeof(char *), (map_data->height + 2));
	while (row_idx < map_data->height)
	{
		map_data->matrix[row_idx]
			= (char *)ft_calloc(sizeof(char), (map_data->width + 1));
		column_idx = 0;
		while (column_idx < map_data->width)
		{
			map_data->matrix[row_idx][column_idx++] = 'x';
		}
		map_data->matrix[row_idx][column_idx] = '\0';
		row_idx++;
	}
	check_values(map_use, map_data);
}
