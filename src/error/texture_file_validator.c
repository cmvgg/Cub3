#include "../../includes/cub3d.h"

static void	validate_path_texture(int index, char **path, char **line)
{
	char	*temp_str;

	*path = ft_strdup("");
	while (((*line)[index] != ' ' && (*line)[index] != '\t') && (*line)[index] != '\0')
	{
		temp_str = *path;
		*path = ft_strjoin(*path, ft_charstr((*line)[index]));
		free(temp_str);
		index++;
	}
	validate_texture_path(*path);
}

void	validate_north_texture(char **line, t_game_elements *elements)
{
	int		i;

	if (elements->counter.north_texture == 1)
		handle_error("Error\nNorth texture is defined more than once");
	elements->counter.north_texture = 1;
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	i += 2;
	while (((*line)[i] == ' ' || (*line)[i] == '\t') && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		handle_error("Error\nNorth texture path is missing");
	validate_path_texture(i, &elements->north.path, line);
}

void	validate_south_texture(char **line, t_game_elements *elements)
{
	int		i;

	if (elements->counter.south_texture == 1)
		handle_error("Error\nSouth texture is defined more than once");
	elements->counter.south_texture = 1;
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	i += 2;
	while (((*line)[i] == ' ' || (*line)[i] == '\t') && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		handle_error("Error\nSouth texture path is missing");
	validate_path_texture(i, &elements->south.path, line);
}

void	validate_west_texture(char **line, t_game_elements *elements)
{
	int		i;

	if (elements->counter.west_texture == 1)
		handle_error("Error\nWest texture is defined more than once");
	elements->counter.west_texture = 1;
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	i += 2;
	while (((*line)[i] == ' ' || (*line)[i] == '\t') && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		handle_error("Error\nWest texture path is missing");
	validate_path_texture(i, &elements->west.path, line);
}

void	validate_east_texture(char **line, t_game_elements *elements)
{
	int		i;

	if (elements->counter.east_texture == 1)
		handle_error("Error\nEast texture is defined more than once");
	elements->counter.east_texture = 1;
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	i += 2;
	while (((*line)[i] == ' ' || (*line)[i] == '\t') && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		handle_error("Error\nEast texture path is missing");
	validate_path_texture(i, &elements->east.path, line);
}

void	validate_sprite_texture(char **line, t_game_elements *elements)
{
	int		i;

	if (elements->counter.sprite == 1)
		handle_error("Error\nSprite texture is defined more than once");
	elements->counter.sprite = 1;
	i = 0;
	while ((*line)[i] == ' ' || (*line)[i] == '\t')
		i++;
	i += 1;
	while (((*line)[i] == ' ' || (*line)[i] == '\t') && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0')
		handle_error("Error\nSprite texture path is missing");
	validate_path_texture(i, &elements->sprite.texture.path, line);
}
