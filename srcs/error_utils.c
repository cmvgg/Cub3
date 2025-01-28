/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:34 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/28 16:30:48 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ext_look_color(int *tot, int count, char *color)
{
	if (color[count] == '\0')
		ft_error("Error: RGB format is invalid\n", color);
	if ((color[count] < '0' || color[count] > '9'))
		ft_error("Error: Colors only can use number\n", color);
	count = 0;
	while (color[count])
	{
		if (color[count] == ',')
			count++;
		if ((color[count] < '0' || color[count] > '9')
			&& (color[count] != ',')
			&& color[count] != ' ' && color[count] != '\t')
			ft_error("Error: RGB format is invalid\n", color);
		count++;
	}
	tot++;
	return (0);
}

static void	final_color(int count, char *str)
{
	while (str[count] == ' ' || str[count] == '\t')
		count++;
	if (str[count] != '\0')
		ft_error("Error: Only use one color\n", str);
}

void	validate_image_path(char *path, char *line)
{
	char	*tmp;
	int		fd;

	tmp = path;
	path = ft_strtrim(path, " \t");
	fd = open(path, O_RDONLY);
	free(tmp);
	if (fd < 0)
	{
		free(path);
		ft_error("Error Path texture is invalid\n", line);
	}
	tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
	if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
	{
		tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
		if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
		{
			free(path);
			ft_error("Error: Extension texture is invalid\n", line);
		}
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
			ft_error("Error: Invalid color\n", color);
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
