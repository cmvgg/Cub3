/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/16 10:30:01 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	draw_sprite_column(int stripe, int height, int **buffer,
		t_data *dsp_dt)
{
	char	*color;
	int		tex_x;
	int		tex_y;

	tex_x = calculate_tex_cor(0, stripe, dsp_dt->spr.width2, dsp_dt);
	if (dsp_dt->spr.dir_y > 0 && stripe > 0 && stripe < dsp_dt->screen_w
		&& dsp_dt->spr.dir_y < dsp_dt->spr.zbuf[stripe])
	{
		dsp_dt->spr.modify = dsp_dt->spr.starty;
		while (dsp_dt->spr.modify < dsp_dt->spr.endy)
		{
			tex_y = calculate_tex_cor(1, dsp_dt->spr.modify, height, dsp_dt);
			color = dsp_dt->spr.addr + (tex_y * dsp_dt->spr.length);
			color += (tex_x * (dsp_dt->spr.bpp / 8));
			if (dsp_dt->spr.modify++
				&& (*(unsigned int *)color & 0x00FFFFFF) != 0)
				buffer[dsp_dt->spr.modify - 1][stripe] = *(unsigned int *)color;
		}
	}
}

void	draw_sprites(int height, int **buffer, t_data *dsp_dt)
{
	int	stripe;

	stripe = dsp_dt->spr.startx;
	while (stripe < dsp_dt->spr.endx)
	{
		draw_sprite_column(stripe, height, buffer, dsp_dt);
		stripe++;
	}
}
