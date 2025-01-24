/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:32:15 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/24 21:12:35 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map_data	*get_map_data(void)
{
	static t_map_data	map;

	return (&map);
}

static void	init_map_data(void)
{
	t_map_data	*map;

	map = get_map_data();
	map->matrix = NULL;
	map->width = 0;
	map->height = 0;
	map->player = -1;
	(void)map;
}

void	ft_error(char *str, char *line)
{
	t_map_data	*map;
	t_data		*dsp_dt;

	if (line)
	{
		printf("\033[0;31mError\n");
		printf("%s", str);
		printf("\n\n\033[0m");
	}
	if (line && *line)
		free(line);
	map = get_map_data();
	while (map->height >= 0)
		free(map->matrix[map->height--]);
	free(map->matrix);
	dsp_dt = get_dsp_data();
	free(dsp_dt->spr.zbuf);
	free(dsp_dt->spr.dist);
	free(dsp_dt->spr.buf);
	free(dsp_dt->spr.order);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_texture_element	element_txt;
	t_map_data			*map;
	char				*tmp;

	element_txt = (t_texture_element){0};
	map = get_map_data();
	init_map_data();
	if (argc == 2)
	{
		tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (tmp && ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0)
		{
			check_elem_texture(argv[1], &element_txt);
			check_validate_map(argv[1], map);
			create_map(argv[1], map);
			cub(&element_txt, map);
			ft_error("", NULL);
			exit(0);
		}
		ft_error("Error: not valid extension\n", *argv);
	}
	ft_error("Error: num of argument is invalid\n", *argv);
}
