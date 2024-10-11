#include "../includes/cub3d.h"

void	handle_error(const char *error_message)
{
	printf("\033[0;31mError\n");
	printf("%s", error_message);
	printf("\n\n\033[0m");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_game_elements	game_elements;
	t_map			map;
	const char		*file_extension;

	file_extension = NULL;
	if (argc != 2)
	{
		handle_error("Invalid number of arguments");
	}
	file_extension = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (!file_extension || ft_strncmp(file_extension, ".cub", ft_strlen(file_extension)) != 0)
	{
		handle_error("Invalid file extension. Expected .cub file");
	}
	game_elements = (t_game_elements){0};
	game_elements.counter = (t_element_counter){0};
	map = (t_map){0};

	check_map_elements(argv[1], &game_elements);
	validate_map(argv[1], &map);
	create_map_from_string(argv[1], &map);
	initialize_game(&game_elements, &map);

	return (EXIT_SUCCESS);
}
