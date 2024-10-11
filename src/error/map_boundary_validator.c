#include "../../includes/cub3d.h"

static int	validate_map_characters(int read_status, char *line, t_map *map_data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == '\f'
			|| line[i] == '\v' || line[i] == '\r')
			handle_error("Error\nOnly space (ASCII 32) is allowed as whitespace");
		if (read_status == -1 || (line[i] != '0' && line[i] != '1'
				&& line[i] != '2' && line[i] != ' '
				&& line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'E' && line[i] != 'W'))
			handle_error("Error\nMap contains invalid characters");
		if ((int)ft_strlen(line) > map_data->width)
			map_data->width = ft_strlen(line);
		i++;
	}
	map_data->height++;
	return (read_status);
}

static void	parse_map_data(int fd, t_map *map_data)
{
	char	*line;
	int		read_status;

	read_status = 1;
	map_data->width = 0;
	map_data->height = 0;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, &line);
		if (*line != '\0')
			break;
		if (read_status == -1 || read_status == 0)
			handle_error("Error\nMap description is missing");
		free(line);
	}
	read_status = validate_map_characters(read_status, line, map_data);
	free(line);
}

void	validate_map_boundaries(const char *map_file, t_map *map_data)
{
	char	*line;
	int		read_status;
	int		fd;
	int		element_count;

	element_count = 0;
	fd = open(map_file, O_RDONLY);
	while (element_count < 8)
	{
		get_next_line(fd, &line);
		if (*line != '\0')
			element_count++;
		free(line);
	}
	parse_map_data(fd, map_data);
	read_status = 1;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, &line);
		read_status = validate_map_characters(read_status, line, map_data);
		free(line);
	}
	close(fd);
}

