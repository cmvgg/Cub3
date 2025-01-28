/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:32:15 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/28 19:07:38 by ivromero         ###   ########.fr       */
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

static void	free_dsptext(t_texture_element *element_txt)
{
	if (element_txt->north_texture.path)
		free(element_txt->north_texture.path);
	if (element_txt->south_texture.path)
		free(element_txt->south_texture.path);
	if (element_txt->west_texture.path)
		free(element_txt->west_texture.path);
	if (element_txt->east_texture.path)
		free(element_txt->east_texture.path);
	if (element_txt->sprite.path)
		free(element_txt->sprite.path);
}

void	ft_error(char *str, char *line)
{
	t_map_data	*map;
	t_data		*dsp_dt;

	dsp_dt = get_dsp_data();
	if (line)
	{
		printf("\033[0;31mError\n");
		printf("%s", str);
		printf("\n\n\033[0m");
	}
	if (line != NULL && line[0] != '\0')
		free_dsptext(dsp_dt->elem_txt);
	if (line && *line)
		free(line);
	map = get_map_data();
	if (map->height > 0)
		while (map->height >= 0)
			free(map->matrix[map->height--]);
	free(map->matrix);
	free(dsp_dt->spr.zbuf);
	free(dsp_dt->spr.dist);
	if (dsp_dt->spr.buf && dsp_dt->spr.buf[0])
		ft_free(dsp_dt->spr.buf);
	free(dsp_dt->spr.order);
	while (get_next_line(get_dsp_data()->fd, &line) > 0)
		free(line);
	get_next_line(get_dsp_data()->fd, &line);
	free(line);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_texture_element	element_txt;
	t_map_data			*map;
	char				*tmp;
	t_data				*dsp_dt;

	dsp_dt = get_dsp_data();
	element_txt = (t_texture_element){0};
	map = get_map_data();
	init_map_data();
	if (argc == 2)
	{
		tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
		if (tmp && ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0)
		{
			dsp_dt->elem_txt = &element_txt;
			check_elem_texture(argv[1], &element_txt);
			check_validate_map(argv[1], map);
			create_map(argv[1], map);
			cub(&element_txt, map);
			ft_error("", NULL);
			exit(0);
		}
		ft_error("Error: not valid extension\n", "");
	}
	ft_error("Error: num of argument is invalid\n", "");
}
