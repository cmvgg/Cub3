/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:46 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 10:07:55 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	close_cub3d(void)
{
	printf("\033[0;32mCub3D cerrado con éxito :)\n\033[0;32m\n");
	exit(0);
}

static void	locate_player(t_data *dsp_dt, t_map_data *map_data)
{
	int	row;
	int	col;

	row = 0;
	while (row < map_data->height)
	{
		col = 0;
		while (col < map_data->width)
		{
			if (map_data->matrix[row][col] == 'N'
				|| map_data->matrix[row][col] == 'S'
				|| map_data->matrix[row][col] == 'E'
				|| map_data->matrix[row][col] == 'W')
			{
				set_dir(map_data->matrix[row][col], dsp_dt);
				dsp_dt->ply.posx = (double)col + 0.2;
				dsp_dt->ply.posy = (double)row + 0.2;
				map_data->matrix[row][col] = '0';
			}
			col++;
		}
		row++;
	}
}

static void	initialize_game_values(t_data *dsp_dt, t_texture_element *elem_txt,
	t_map_data *map_dt)
{
	int	red;
	int	green;
	int	blue;

	red = 0;
	green = 0;
	blue = 0;
	dsp_dt->map.board = map_dt->matrix;
	dsp_dt->screen_w = elem_txt->resolution.width;
	dsp_dt->screen_h = elem_txt->resolution.height;
	red = elem_txt->color.cl_red << 16;
	green = elem_txt->color.cl_green << 8;
	blue = elem_txt->color.cl_blue;
	dsp_dt->map.sky = red + green + blue;
	red = elem_txt->color.fl_red << 16;
	green = elem_txt->color.fl_green << 8;
	blue = elem_txt->color.fl_blue;
	dsp_dt->map.floor = red + green + blue;
	dsp_dt->key.move_up = 0;
	dsp_dt->key.move_down = 0;
	dsp_dt->key.move_right = 0;
	dsp_dt->key.move_left = 0;
	dsp_dt->key.rot_left = 0;
	dsp_dt->key.rot_right = 0;
	dsp_dt->key.destroy = 0;
}

static void	initialize_textures(t_data *dsp_dt, t_texture_element *elem_texture)
{
	dsp_dt->nor.path = ft_strtrim(elem_texture->north_texture.path, " \t");
	north_texture(dsp_dt);
	dsp_dt->sou.path = ft_strtrim(elem_texture->south_texture.path, " \t");
	south_texture(dsp_dt);
	dsp_dt->eas.path = ft_strtrim(elem_texture->east_texture.path, " \t");
	east_texture(dsp_dt);
	dsp_dt->wes.path = ft_strtrim(elem_texture->west_texture.path, " \t");
	west_texture(dsp_dt);
	dsp_dt->spr.path = ft_strtrim(elem_texture->sprite.path, " \t");
	sprite_texture(dsp_dt);
	dsp_dt->mlx.win = mlx_new_window(dsp_dt->mlx.mlx,
			dsp_dt->screen_w, dsp_dt->screen_h, "cub");
	dsp_dt->mlx.img = mlx_new_image(dsp_dt->mlx.mlx,
			dsp_dt->screen_w, dsp_dt->screen_h);
	dsp_dt->mlx.addr = mlx_get_data_addr(dsp_dt->mlx.img,
			&dsp_dt->mlx.bpp, &dsp_dt->mlx.length, &dsp_dt->mlx.end);
}

void	cub(t_texture_element *elem_texture, t_map_data *map_data)
{
	t_data	dsp_dt;
	int		screen_max_width;
	int		screen_max_height;

	screen_max_height = 0;
	screen_max_width = 0;
	dsp_dt.mlx.mlx = mlx_init();
	locate_player(&dsp_dt, map_data);
	initialize_game_values(&dsp_dt, elem_texture, map_data);
	initialize_textures(&dsp_dt, elem_texture);
	find_sprites(&dsp_dt, map_data);
	mlx_get_screen_size(dsp_dt.mlx.mlx, &screen_max_width, &screen_max_height);
	if (dsp_dt.screen_w > screen_max_width)
		dsp_dt.screen_w = screen_max_width;
	if (dsp_dt.screen_h > screen_max_height)
		dsp_dt.screen_h = screen_max_height;
	mlx_hook(dsp_dt.mlx.win, 2, 1L << 0, key_press, &dsp_dt);
	mlx_hook(dsp_dt.mlx.win, 3, 1L << 1, key_release, &dsp_dt);
	mlx_hook(dsp_dt.mlx.win, 17, 1L << 17, close_cub3d, &dsp_dt);
	mlx_loop_hook(dsp_dt.mlx.mlx, render_frame, &dsp_dt);
	mlx_loop(dsp_dt.mlx.mlx);
}
