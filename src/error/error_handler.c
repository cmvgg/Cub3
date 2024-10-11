#include "../../includes/cub3d.h"

static void	validate_element(int index, char identifier, char **line, t_game_elements *elements)
{
	if (identifier == 'R' && ((*line)[index + 1] == ' ' || (*line)[index + 1] == '\t'))
		validate_resolution(line, elements);
	else if (identifier == 'N' && ((*line)[index + 2] == ' ' || (*line)[index + 2] == '\t'))
		validate_north_texture(line, elements);
	else if (identifier == 'S' && ((*line)[index + 2] == ' ' || (*line)[index + 2] == '\t'))
		validate_south_texture(line, elements);
	else if (identifier == 'W' && ((*line)[index + 2] == ' ' || (*line)[index + 2] == '\t'))
		validate_west_texture(line, elements);
	else if (identifier == 'E' && ((*line)[index + 2] == ' ' || (*line)[index + 2] == '\t'))
		validate_east_texture(line, elements);
	else if (identifier == 'S' && ((*line)[index + 1] == ' ' || (*line)[index + 1] == '\t'))
		validate_sprite_texture(line, elements);
	else if (identifier == 'F' && ((*line)[index + 1] == ' ' || (*line)[index + 1] == '\t'))
		validate_floor_color(line, elements);
	else if (identifier == 'C' && ((*line)[index + 1] == ' ' || (*line)[index + 1] == '\t'))
		validate_ceiling_color(line, elements);
	else
		handle_error("Error\nInvalid texture/resolution format");
}

static void	identify_element(char **line, t_game_elements *elements)
{
	int	i;

	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	if ((*line)[i] == 'R')
		validate_element(i, 'R', line, elements);
	else if ((*line)[i] == 'N' && (*line)[i + 1] == 'O')
		validate_element(i, 'N', line, elements);
	else if ((*line)[i] == 'S' && (*line)[i + 1] == 'O')
		validate_element(i, 'S', line, elements);
	else if ((*line)[i] == 'W' && (*line)[i + 1] == 'E')
		validate_element(i, 'W', line, elements);
	else if ((*line)[i] == 'E' && (*line)[i + 1] == 'A')
		validate_element(i, 'E', line, elements);
	else if ((*line)[i] == 'S')
		validate_element(i, 'S', line, elements);
	else if ((*line)[i] == 'F')
		validate_element(i, 'F', line, elements);
	else if ((*line)[i] == 'C')
		validate_element(i, 'C', line, elements);
	else
		handle_error("Error\nInvalid texture/resolution format");
}

static int	process_identifier(int read_status, int element_count, char **line, t_game_elements *elements)
{
	if (read_status == -1 || !(*line))
		return (-1);
	if (read_status == 0 && element_count < 7)
		handle_error("Error\nInvalid .cub file format");
	if (**line == '\0')
		return (0);
	identify_element(line, elements);
	return (1);
}

void	check_map_elements(const char *map_file, t_game_elements *elements)
{
	char	*line = NULL;
	int		element_count;
	int		read_status;
	int		fd;

	element_count = 0;
	read_status = 1;
	fd = 0;
	fd = open(map_file, O_RDONLY);
	if (fd <= 0)
		handle_error("Error\nMap file not found");
	while (line && read_status == 1)
	{
		read_status = get_next_line(fd, &line);
		read_status = process_identifier(read_status, element_count, &line, elements);
		free(line);
		if (read_status == -1)
			handle_error("Error\nInvalid identifier");
		read_status = 1;
		element_count++;
	}
	while (get_next_line(fd, &line) == 1)
		free(line);
	free(line);
	close(fd);
}
