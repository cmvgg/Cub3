#include "../includes/cub3d.h"

void	ft_error(char *str)
{
	printf("\033[0;31mError\n");
	printf("%s", str);
	printf("\n\n\033[0m");
	exit(0);
}


int	main(int argc, char *argv[])
{
	t_texture_element	element_txt;
	t_map_data	map;
	char	*tmp;

	element_txt = (t_texture_element){0};
	map = (t_map_data){0};
	if (argc == 2)
	{
		tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (tmp && ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0)
		{
			check_elem_texture(argv[1], &element_txt);
			check_validate_map(argv[1], &map);
			create_map(argv[1], &map);
			cub(&element_txt, &map);
			exit(0);
		}
		ft_error("Error: not valid extension\n");
	}
	ft_error("Error: num of argument is invalid\n");
}
 