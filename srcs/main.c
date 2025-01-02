/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:32:15 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/02 23:30:57 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(char *str)
{
	printf("\033[0;31mError\n");
	printf("%s", str);
	printf("\n\n\033[0m");
	exit(0);
}

int main(int argc, char **argv)
{
	t_texture_element	element_txt;
	t_map_data			map;
	char				*tmp;

	element_txt = (t_texture_element){0};
	map = (t_map_data){
		.matrix = NULL, 
		.width = 0,
		.height = 0,
		.player = -1
	};
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
