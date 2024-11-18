/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:43 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:51:44 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	validate_texture_data(int idx, char ident, char **ln,
		t_texture_element *elem_texture)
{
	if (ident == 'R' && ((*ln)[idx + 1] == ' ' || (*ln)[idx + 1] == '\t'))
		error_resolution(ln, elem_texture);
	else if (ident == 'N' && ((*ln)[idx + 2] == ' ' || (*ln)[idx + 2] == '\t'))
		error_north(ln, elem_texture);
	else if (ident == 'S' && ((*ln)[idx + 2] == ' ' || (*ln)[idx + 2] == '\t'))
		error_south(ln, elem_texture);
	else if (ident == 'W' && ((*ln)[idx + 2] == ' ' || (*ln)[idx + 2] == '\t'))
		error_west(ln, elem_texture);
	else if (ident == 'E' && ((*ln)[idx + 2] == ' ' || (*ln)[idx + 2] == '\t'))
		error_east(ln, elem_texture);
	else if (ident == 'P' && ((*ln)[idx + 1] == ' ' || (*ln)[idx + 1] == '\t'))
		error_sprite(ln, elem_texture);
	else if (ident == 'F' && ((*ln)[idx + 1] == ' ' || (*ln)[idx + 1] == '\t'))
		error_floor(ln, elem_texture);
	else if (ident == 'C' && ((*ln)[idx + 1] == ' ' || (*ln)[idx + 1] == '\t'))
		error_skying(ln, elem_texture);
	else
		ft_error("Error:\n");
}

static void	extract_map_textures(char **line, t_texture_element *elem_texture)
{
	int	index;

	index = 0;
	while ((*line)[index] == ' ' || (*line)[index] == '\t')
		index++;
	if ((*line)[index] == 'R')
		validate_texture_data(index, 'R', line, elem_texture);
	else if ((*line)[index] == 'N' && (*line)[index + 1] == 'O')
		validate_texture_data(index, 'N', line, elem_texture);
	else if ((*line)[index] == 'S' && (*line)[index + 1] == 'O')
		validate_texture_data(index, 'S', line, elem_texture);
	else if ((*line)[index] == 'W' && (*line)[index + 1] == 'E')
		validate_texture_data(index, 'W', line, elem_texture);
	else if ((*line)[index] == 'E' && (*line)[index + 1] == 'A')
		validate_texture_data(index, 'E', line, elem_texture);
	else if ((*line)[index] == 'S')
		validate_texture_data(index, 'P', line, elem_texture);
	else if ((*line)[index] == 'F')
		validate_texture_data(index, 'F', line, elem_texture);
	else if ((*line)[index] == 'C')
		validate_texture_data(index, 'C', line, elem_texture);
	else
		ft_error("Error:\n");
}

static int	handle_identify(int read_stat, int identify_count, char **line,
		t_texture_element *elem_texture)
{
	if (read_stat == -1 || !(*line))
		return (-1);
	if (read_stat == 0 && identify_count < 7)
		ft_error("Error:\n");
	if (**line == '\0')
		return (0);
	extract_map_textures(line, elem_texture);
	return (1);
}

void	check_elem_texture(const char *map_use, t_texture_element *elem_txt)
{
	char	*line;
	int		element_count;
	int		read_stat;
	int		fd;

	element_count = 0;
	read_stat = 1;
	fd = open(map_use, O_RDONLY);
	if (fd < 0)
		ft_error("Error:\n");
	while (element_count < 8 && read_stat == 1)
	{
		read_stat = get_next_line(fd, &line);
		read_stat = handle_identify(read_stat, element_count, &line, elem_txt);
		free(line);
		if (read_stat == -1)
			ft_error("Error:\n");
		if (read_stat == 1)
			element_count++;
		read_stat = 1;
	}
	while (get_next_line(fd, &line) == 1)
		free(line);
	free(line);
	close(fd);
}
