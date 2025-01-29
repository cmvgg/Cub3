/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_imap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:14 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/29 11:53:11 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	elem_texture_to_map(int fd, char **current_line)
{
	int		read_status;

	read_status = 1;
	free(*current_line);
	while (read_status == 1)
	{
		read_status = get_next_line(fd, current_line);
		if (**current_line != '\0')
		{
			ft_free_gnl_static();
			break ;
		}
		free(*current_line);
		ft_free_gnl_static();
	}
}

static void	check_values(const char *map_use, t_map_data *map_data)
{
	char	*current_line;
	int		count;
	int		fd;

	count = 0;
	fd = open(map_use, O_RDONLY);
	while (count <= 7 && get_next_line(fd, &current_line))
	{
		if (*current_line)
			count++;
		if (count == 7)
			break ;
		free(current_line);
		ft_free_gnl_static();
	}
	elem_texture_to_map(fd, &current_line);
	map_data->player = 0;
	validate_map_first_line(&current_line, map_data);
	validate_map_lines(fd, &current_line, map_data);
	if (map_data->player == 0)
		ft_error("Error: No player\n", current_line);
	validate_map_last_line(current_line, map_data);
	free(current_line);
	current_line = NULL;
	close(fd);
}

void	create_map(const char *map_use, t_map_data *map_data)
{
	int	row_idx;
	int	column_idx;

	row_idx = 0;
	map_data->matrix
		= (char **)ft_calloc(sizeof(char *), (map_data->height + 2));
	while (row_idx < (map_data->height))
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
