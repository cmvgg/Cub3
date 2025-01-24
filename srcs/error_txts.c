/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_txts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:27 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/24 18:21:45 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_north(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.texture_north == 1)
		ft_error("Error:\n", *line);
	elem_texture->graphics.texture_north = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 2;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:\n", *line);
	copy_path(count, &str, line);
	elem_texture->north_texture.path = ft_strdup(str);
	validate_image_path(elem_texture->north_texture.path);
	elem_texture->north_texture.path = str;
}

void	error_south(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.texture_south == 1)
		ft_error("Error: \n", *line);
	elem_texture->graphics.texture_south = 1;
	count = 0;
	while (((*line)[count] == ' ' || (*line)[count] == '\t'))
		count++;
	count += 2;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error: \n", *line);
	copy_path(count, &str, line);
	elem_texture->south_texture.path = ft_strdup(str);
	validate_image_path(elem_texture->south_texture.path);
	elem_texture->south_texture.path = str;
}

void	error_west(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.texture_west == 1)
		ft_error("Error: \n", *line);
	elem_texture->graphics.texture_west = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 2;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error: \n", *line);
	copy_path(count, &str, line);
	elem_texture->west_texture.path = ft_strdup(str);
	validate_image_path(elem_texture->west_texture.path);
	elem_texture->west_texture.path = str;
}

void	error_east(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.texture_east == 1)
		ft_error("Error:\n", *line);
	elem_texture->graphics.texture_east = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 2;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:\n", *line);
	copy_path(count, &str, line);
	elem_texture->east_texture.path = ft_strdup(str);
	validate_image_path(elem_texture->east_texture.path);
	elem_texture->east_texture.path = str;
}

void	error_sprite(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.sprite_texture == 1)
		ft_error("Error:\n", *line);
	elem_texture->graphics.sprite_texture = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:\n", *line);
	copy_path(count, &str, line);
	elem_texture->sprite.path = ft_strdup(str);
	validate_image_path(elem_texture->sprite.path);
	elem_texture->sprite.path = str;
}
