/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:34 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/29 18:09:16 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_free3(char *str, char *text, char **line)
{
	free(*line);
	ft_error(text, str);
}

static int	ext_look_color(int *tot, int count, char *color, char **line)
{
	if (color[count] == '\0')
		ft_free3(color, "Error: RGB format is invalid\n", line);
	if ((color[count] < '0' || color[count] > '9'))
		ft_free3(color, "Error: Colors only can use number\n", line);
	count = 0;
	while (color[count])
	{
		if (color[count] == ',')
			count++;
		if ((color[count] < '0' || color[count] > '9')
			&& (color[count] != ',')
			&& color[count] != ' ' && color[count] != '\t')
			ft_free3(color, "Error: RGB format is invalid\n", line);
		count++;
	}
	tot++;
	return (0);
}

static void	final_color(int count, char *str, char **line)
{
	while (str[count] == ' ' || str[count] == '\t')
		count++;
	if (str[count] != '\0')
		ft_free3(str, "Error: Only use one color\n", line);
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
		ft_free3(line, "Error Path texture is invalid\n", &path);
	tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
	if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
	{
		tmp = ft_strnstr(path + ft_strlen(path) - 4, ".xpm", ft_strlen(path));
		if (!tmp || ft_strncmp(tmp, ".xpm", ft_strlen(tmp)) != 0)
			ft_free3(line, "Error: Extension texture is invalid\n", &path);
	}
	free(path);
	close(fd);
}

int	look_color(int *red, int *green, char *color, char **line)
{
	int	tot;
	int	count;
	int	value;

	tot = 0;
	count = 0;
	value = 0;
	while (tot < 3)
	{
		value = ext_look_color(&tot, count, color, line);
		while (color[count] >= '0' && color[count] <= '9')
			value = (value * 10) + (color[count++] - '0');
		if ((tot < 2 && color[count] != ',') || (value < 0 || value > 255))
			ft_free3(color, "Error: Only use one color\n", line);
		if (tot == 0)
			(*red) = value;
		else if (tot == 1)
			(*green) = value;
		count++;
		tot++;
	}
	count--;
	final_color(count, color, line);
	return (value);
}
