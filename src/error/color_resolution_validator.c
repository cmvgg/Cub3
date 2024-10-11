#include "../../includes/cub3d.h"

static int	parse_resolution_value(int is_first_value, int index, char **value, char **line)
{
	char	*temp_str;
	char	*temp_char;

	(*value) = ft_strdup("");
	if ((*line)[index] == 'R')
		index++;
	while ((*line)[index] == ' ' || (*line)[index] == '\t')
		index++;
	while ((*line)[index] != ' ' && (*line)[index] != '\t' && (*line)[index] != '\0')
	{
		if ((*line)[index] < '0' || (*line)[index] > '9')
		
			handle_error("Error\nResolution contains non-numeric characters");
		temp_str = (*value);
		temp_char = ft_charstr((*line)[index]);
		(*value) = ft_strjoin(*value, temp_char);
		free(temp_str);
		free(temp_char);
		index++;
	}
	while (((*line)[index] == ' ' || (*line)[index] == '\t') && (*line)[index] != '\0')
		index++;
	if (((*line)[index] == '\0' && is_first_value) || ((*line)[index] != '\0' && !is_first_value))
		handle_error("Error\nResolution requires exactly two values");
	return (index);
}

static void	parse_path(int index, char **path, char **line)
{
	char	*temp_str;
	char	*temp_char;

	(*path) = ft_strdup("");
	while (((*line)[index] != ' ' && (*line)[index] != '\t') && (*line)[index] != '\0')
	{
		temp_str = (*path);
		temp_char = ft_charstr((*line)[index]);
		(*path) = ft_strjoin(*path, temp_char);
		free(temp_str);
		free(temp_char);
		index++;
	}
	while ((*line)[index] != '\0')
	{
		if ((*line)[index] != ' ' && (*line)[index] != '\t')
			handle_error("Error\nElement has incorrect format");
		index++;
	}
}

void	validate_resolution(char **line, t_game_elements *elements)
{
	char	*resolution_str;
	int		index;

	if (elements->counter.resolution == 1)
		handle_error("Error\nResolution is defined more than once");
	elements->counter.resolution = 1;
	index = 1;
	while (((*line)[index] == ' ' || (*line)[index] == '\t') && (*line)[index] != '\0')
		index++;
	if ((*line)[index] == '\0')
		handle_error("Error\nInvalid resolution format");
	index = parse_resolution_value(1, index, &resolution_str, line);
	elements->resolution.width = ft_atoi(resolution_str);
	free(resolution_str);
	index = parse_resolution_value(0, index, &resolution_str, line);
	elements->resolution.height = ft_atoi(resolution_str);
	free(resolution_str);
	if (elements->resolution.width <= 0 || elements->resolution.height <= 0)
		handle_error("Error\nInvalid resolution values");
}

void	validate_floor_color(char **line, t_game_elements *elements)
{
	char	*color_str;
	int		index;
	int		red;
	int		green;

	if (elements->counter.floor_color == 1)
		handle_error("Error\nFloor color is defined more than once");
	elements->counter.floor_color = 1;
	index = 0;
	while ((*line)[index] == ' ' || (*line)[index] == '\t')
		index++;
	index++;
	while (((*line)[index] == ' ' || (*line)[index] == '\t') && (*line)[index] != '\0')
		index++;
	if ((*line)[index] == '\0')
		handle_error("Error\nFloor color is missing");
	parse_path(index, &color_str, line);
	elements->color.floor = color_str;
	elements->color.floor_rgb[2] = parse_color_string(&red, &green, color_str);
	elements->color.floor_rgb[1] = green;
	elements->color.floor_rgb[0] = red;
}

void	validate_ceiling_color(char **line, t_game_elements *elements)
{
	char	*color_str;
	int		index;
	int		red;
	int		green;

	if (elements->counter.ceiling_color == 1)
		handle_error("Error\nCeiling color is defined more than once");
	elements->counter.ceiling_color = 1;
	index = 0;
	while ((*line)[index] == ' ' || (*line)[index] == '\t')
		index++;
	index++;
	while (((*line)[index] == ' ' || (*line)[index] == '\t') && (*line)[index] != '\0')
		index++;
	if ((*line)[index] == '\0')
		handle_error("Error\nCeiling color is missing");
	parse_path(index, &color_str, line);
	elements->color.ceiling = color_str;
	elements->color.ceiling_rgb[2] = parse_color_string(&red, &green, color_str);
	elements->color.ceiling_rgb[1] = green;
	elements->color.ceiling_rgb[0] = red;
}