/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_colres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:59 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/05 21:40:01 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	copy_res(int loop, int ct, char **str, char **ln)
{
	char	*tmp1;
	char	*tmp2;

	(*str) = ft_strdup("");
	if ((*ln)[ct] == 'R')
		ct++;
	while ((*ln)[ct] == ' ' || (*ln)[ct] == '\t')
		ct++;
	while ((*ln)[ct] != ' ' && (*ln)[ct] != '\t' && (*ln)[ct] != '\0')
	{
		if ((*ln)[ct] < '0' || (*ln)[ct] > '9')
			ft_error("Error:c1\n");
		tmp1 = (*str);
		tmp2 = ft_charstr((*ln)[ct++]);
		(*str) = ft_strjoin(*str, tmp2);
		free(tmp1);
		free(tmp2);
	}
	while (((*ln)[ct] == ' ' || (*ln)[ct] == '\t')
		&& (*ln)[ct] != '\0')
		ct++;
	if (((*ln)[ct] == '\0' && loop == 1)
		|| ((*ln)[ct] != '\0' && loop == 2))
		ft_error("Error:c2\n");
	return (ct);
}

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
			ft_error("Error:c3\n");
		count++;
	}
}

void	error_resolution(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;

	if (elem_texture->graphics.resolution == 1)
		ft_error("Error:c4\n");
	elem_texture->graphics.resolution = 1;
	count = 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:c5n");
	count = copy_res(1, count, &str, line);
	elem_texture->resolution.width = ft_atoi(str);
	copy_res(2, count, &str, line);
	elem_texture->resolution.height = ft_atoi(str);
	free(str);
	str = NULL;
	if (elem_texture->resolution.width <= 0
		|| elem_texture->resolution.height <= 0)
		ft_error("Error:c6\n");
}

void	error_floor(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;
	int		red;
	int		green;

	if (elem_texture->graphics.floor_color == 1)
		ft_error("Error:c7\n");
	elem_texture->graphics.floor_color = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:c8\n");
	copy_path(count, &str, line);
	elem_texture->color.floor = str;
	elem_texture->color.fl_blue = look_color(&red, &green, str);
	elem_texture->color.fl_green = green;
	elem_texture->color.fl_red = red;
}

void	error_skying(char **line, t_texture_element *elem_texture)
{
	char	*str;
	int		count;
	int		red;
	int		green;

	if (elem_texture->graphics.skying_color == 1)
		ft_error("Error:c9\n");
	elem_texture->graphics.skying_color = 1;
	count = 0;
	while ((*line)[count] == ' ' || (*line)[count] == '\t')
		count++;
	count += 1;
	while (((*line)[count] == ' ' || (*line)[count] == '\t')
		&& (*line)[count] != '\0')
		count++;
	if ((*line)[count] == '\0')
		ft_error("Error:c10\n");
	copy_path(count, &str, line);
	elem_texture->color.skying = str;
	elem_texture->color.cl_blue = look_color(&red, &green, str);
	elem_texture->color.cl_green = green;
	elem_texture->color.cl_red = red;
}
