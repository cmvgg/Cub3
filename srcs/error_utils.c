/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:34 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/02 23:30:39 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ext_look_color(int *tot, int count, char *color)
{
	if (color[count] == '\0')
		ft_error("Error:\n");
	if ((color[count] < '0' || color[count] > '9'))
		ft_error("Error:\n");
	count = 0;
	while (color[count])
	{
		if (color[count] == ',')
			count++;
		if ((color[count] < '0' || color[count] > '9')
			&& (color[count] != ',')
			&& color[count] != ' ' && color[count] != '\t')
			ft_error("Error:\n");
		count++;
	}
	tot++;
	return (0);
}

static void	final_color(int count, char const *str)
{
	while (str[count] == ' ' || str[count] == '\t')
		count++;
	if (str[count] != '\0')
		ft_error("Error:\n");
}

void	validate_image_path(char *path)
{
	char	*tmp;
	int		fd;

	tmp = path;
	path = ft_strtrim(path, " \t");
	fd = open(path, O_RDONLY);
	free(tmp);
	if (fd < 0)
	{
		//close(fd);
		ft_error("Error\n");
	}
	tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
	if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
	{
		tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
		if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
			ft_error("Error:\n");
	}
	free(path);
	close(fd);
}

int	look_color(int *red, int *green, char *color)
{
	int	tot;
	int	count;
	int	value;

	tot = 0;
	count = 0;
	value = 0;
	while (tot < 3)
	{
		value = ext_look_color(&tot, count, color);
		while (color[count] >= '0' && color[count] <= '9')
			value = (value * 10) + (color[count++] - '0');
		if ((tot < 2 && color[count] != ',') || (value < 0 || value > 255))
			ft_error("Error:\n");
		if (tot == 0)
			(*red) = value;
		else if (tot == 1)
			(*green) = value;
		count++;
		tot++;
	}
	count--;
	final_color(count, color);
	return (value);
}
