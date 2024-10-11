#include "../../includes/cub3d.h"

static void	validate_rgb_format(const char *color_string)
{
	int comma_count;
	int i;

	comma_count = 0;
	i = 0;
	while (color_string[i] != '\0')
	{
		if (color_string[i] == ',')
		{
			comma_count++;
			if (comma_count > 2)
			{
				handle_error("Invalid RGB format: too many commas");
			}
		}
		else if (!ft_isdigit(color_string[i]) && !ft_isspace(color_string[i]))
		{
			handle_error("Invalid RGB format: non-digit characters found");
		}
		i++;
	}
	if (comma_count != 2)
	{
		handle_error("Invalid RGB format: incorrect number of commas");
	}
}

static void	validate_single_color(const char *color_string)
{
	while (*color_string == ' ' || *color_string == '\t')
		color_string++;
	if (*color_string != '\0')
	{
		handle_error("Invalid color format: extra characters after color definition");
	}
}

void	validate_texture_path(char *path)
{
	char	*trimmed_path;
	int		fd;

	fd = 0;
	trimmed_path = ft_strtrim(path, " \t");
	if (!trimmed_path)
	{
		handle_error("Memory allocation failed for trimmed path");
	}
	fd = open(trimmed_path, O_RDONLY);
	if (fd <= 0)
	{
		free(trimmed_path);
		handle_error("Texture file not found or inaccessible");
	}
	if (!ft_strnstr(trimmed_path + ft_strlen(trimmed_path) - 4, ".xpm", 4))
	{
		free(trimmed_path);
		close(fd);
		handle_error("Invalid texture file extension");
	}
	free(trimmed_path);
	close(fd);
}

int	parse_color_string(int *red, int *green, const char *color_string)
{
	int		values[3];
	int		value_index;
	int		current_value;
	const char	*ptr;

	value_index = 0;
	ptr = NULL;
	current_value = 0;
	validate_rgb_format(color_string);
	ptr = color_string;
	while (value_index < 3)
	{
		current_value = 0;
		while (ft_isdigit(*ptr))
		{
			current_value = (current_value * 10) + (*ptr - '0');
			ptr++;
		}
		if (current_value < 0 || current_value > 255)
			handle_error("Color value out of range (0-255)");
		values[value_index] = current_value;
		if (value_index < 2 && *ptr != ',')
			handle_error("Invalid color format: missing comma");
		ptr++;
		value_index++;
	}
	validate_single_color(ptr);
	*red = values[0];
	*green = values[1];
	return values[2];
}
