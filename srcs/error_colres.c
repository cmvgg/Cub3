/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_colres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:59 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/28 18:13:16 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_path(int count, char **str, char **line)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	(*str) = ft_strdup("");
	while (((*line)[count] != ' ' || (*line)[count] != '\t')
		&& (*line)[count] != '\0')
	{
		tmp1 = (*str);
		tmp2 = ft_charstr((*line)[count++]);
		if (*str)
			(*str) = ft_strjoin(*str, tmp2);
		free(tmp1);
		free(tmp2);
	}
	while ((*line)[count] != '\0')
	{
		if ((*line)[count] != ' ' && (*line)[count] != '\t')
			ft_error("Error: Format element incorrect\n", *line);
		count++;
	}
}

void	error_floor(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;
	int		red;
	int		green;

	if (elem_texture->graphics.floor_color == 1)
		ft_error("Error: Repeat floor texture\n", *line);
	elem_texture->graphics.floor_color = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error: Not path texture floor\n", *line);
	copy_path(count, &str, line);
	elem_texture->color.floor = str;
	elem_texture->color.fl_blue = look_color(&red, &green, str);
	elem_texture->color.fl_green = green;
	elem_texture->color.fl_red = red;
	free(str);
}

void	error_skying(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;
	int		red;
	int		green;

	if (elem_texture->graphics.skying_color == 1)
		ft_error("Error: Repeat sky texture\n", *line);
	elem_texture->graphics.skying_color = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error: Not path texture sky\n", *line);
	copy_path(count, &str, line);
	elem_texture->color.skying = str;
	elem_texture->color.cl_blue = look_color(&red, &green, str);
	elem_texture->color.cl_green = green;
	elem_texture->color.cl_red = red;
	free(str);
}
