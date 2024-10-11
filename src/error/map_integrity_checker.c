#include "../../includes/cub3d.h"

static void	skip_empty_lines(int fd, char **line)
{
	int		read_status;

	read_status = 1;
	while (read_status == 1)
	{
		read_status = get_next_line(fd, line);
		if (**line != '\0')
			break;
		free(*line);
	}
}

static void	validate_map_content(const char *map_file, t_map *map)
{
	char	*line;
	int		read_count;
	int		ini;
	int		fd;

	read_count = 0;
	ini = 0;
	fd = open(map_file, O_RDONLY);
	get_next_line(fd, &line);
	while (line != NULL && (*line == '\0' || line[0] == '\0'))
	{
		printf("\n\n%i\n\n", line[0]);
		if (*line != '\0')
			read_count++;
		printf("\n%i\n", read_count);
		free(line);
		line = NULL;
		get_next_line(fd, &line);
		if(line)
			printf("+++%s+++", line);
	}
	free (line);
	skip_empty_lines(fd, &line);
	map->grid = ft_calloc(sizeof(char *), read_count + 1);
	ini = read_count;
	while (ini >= 0)
	map->grid[ini--] = ft_calloc(sizeof(char), read_count);
	map->player_count = 0;
	parse_map_first_line(&line, map);
	parse_map_body(fd, &line, map);	
	if (map->player_count == 0)
		handle_error("Error\nNo player found in the map");
	parse_map_last_line(&line, map);
	close(fd);
}

void	create_map_from_string(const char *map_string, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	while (i < map->height)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * (map->width + 1));
		j = 0;
		while (j < map->width)
		{
			map->grid[i][j] = 'x';
			j++;
		}
		map->grid[i][j] = '\0';
		i++;
	}
	validate_map_content(map_string, map);
}
