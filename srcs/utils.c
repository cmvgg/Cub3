/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:52 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:55:01 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *dsp_dt, int x, int y, int color)
{
	char	*dst;

	dst = dsp_dt->mlx.addr + (y * dsp_dt->mlx.length) + (x * (dsp_dt->mlx.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	init_buffer(int mode, int ***buffer, t_data *dsp_dt)
{
	int	x;

	if (mode == 1)
	{
		x = 0;
		(*buffer) = (int **)ft_calloc(sizeof(int *), dsp_dt->screen_h);
		while (x < dsp_dt->screen_h)
		{
			(*buffer)[x] = (int *)ft_calloc(sizeof(int), dsp_dt->screen_w);
			x++;
		}
	}
	else if (mode == 0)
	{
		x = 0;
		while (x < dsp_dt->screen_h)
			free((*buffer)[x++]);
		free(*buffer);
	}
}

void	draw_buffer(int **buffer, t_data *dsp_dt)
{
	int	count_y;
	int	count_x;

	count_y = 0;
	while (count_y < dsp_dt->screen_h)
	{
		count_x = 0;
		while (count_x < dsp_dt->screen_w)
		{
			my_mlx_pixel_put(dsp_dt, count_x, count_y,
				buffer[count_y][count_x]);
			count_x++;
		}
		count_y++;
	}
}

static int	calculate_tex_cor(int mode, int cor, int size, t_data *dsp_dt)
{
	int	result;

	if (mode == 0)
	{
		result = (int)((cor - (-size / 2 + dsp_dt->spr.screenx))
				* dsp_dt->spr.width / size);
		return (result);
	}
	else if (mode == 1)
	{
		result = cor * 256 - dsp_dt->screen_h * 128 + size * 128;
		result = ((result * dsp_dt->spr.height) / size) / 256;
		return (result);
	}
	return (-1);
}

void	draw_sprites(int width, int height, int **buffer, t_data *dsp_dt)
{
	char	*color;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		y;

	stripe = dsp_dt->spr.startx;
	color = NULL;
	tex_x = 0;
	tex_y = 0;
	y = 0;
	while (stripe < dsp_dt->spr.endx)
	{
		tex_x = calculate_tex_cor(0, stripe, width, dsp_dt);
		if (dsp_dt->spr.dir_y > 0 && stripe > 0 && stripe < dsp_dt->screen_w
			&& dsp_dt->spr.dir_y < dsp_dt->spr.zbuf[stripe])
		{
			y = dsp_dt->spr.starty;
			while (y < dsp_dt->spr.endy)
			{
				tex_y = calculate_tex_cor(1, y, height, dsp_dt);
				color = dsp_dt->spr.addr + (tex_y * dsp_dt->spr.length);
				color += (tex_x * (dsp_dt->spr.bpp / 8));
				if (y++ && (*(unsigned int *)color & 0x00FFFFFF) != 0)
					buffer[y - 1][stripe] = *(unsigned int *)color;
			}
		}
		stripe++;
	}
}
