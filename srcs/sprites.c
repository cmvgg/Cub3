/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/12 19:47:24 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_sprites_dist(t_data *dsp_dt)
{
	int	y;
	int	index;

	y = 0;
	index = -1;
	while (y < dsp_dt->spr.tot)
	{
		dsp_dt->spr.order[y] = (double)y;
		dsp_dt->spr.dist[y] = pow(dsp_dt->ply.posx - dsp_dt->spr.buf[y][1], 2);
		dsp_dt->spr.dist[y] += pow(dsp_dt->ply.posy - dsp_dt->spr.buf[y][0], 2);
		y++;
	}
	sort_sprites(dsp_dt->spr.order, dsp_dt->spr.dist, dsp_dt->spr.tot, index);
}

static void	get_sprite_values(int y, t_data *dsp)
{
	double	invmatrix;

	dsp->spr.posx = dsp->spr.buf[(int)dsp->spr.order[y]][1] - dsp->ply.posx;
	dsp->spr.posy = dsp->spr.buf[(int)dsp->spr.order[y]][0] - dsp->ply.posy;
	invmatrix = 1 / (dsp->ply.plnx * dsp->ply.dir_y
			- dsp->ply.dir_x * dsp->ply.plny);
	dsp->spr.dir_x = (dsp->ply.dir_y * dsp->spr.posx
			- dsp->ply.dir_x * dsp->spr.posy);
	dsp->spr.dir_x *= invmatrix;
	dsp->spr.dir_y = (-dsp->ply.plny * dsp->spr.posx
			+ dsp->ply.plnx * dsp->spr.posy);
	dsp->spr.dir_y *= invmatrix;
}

static void	get_sprite_height(int *height, t_data *dsp_dt)
{
	(*height) = abs((int)(dsp_dt->screen_h / dsp_dt->spr.dir_y));
	dsp_dt->spr.starty = dsp_dt->screen_h / 2 - (*height) / 2;
	if (dsp_dt->spr.starty < 0)
		dsp_dt->spr.starty = 0;
	dsp_dt->spr.endy = dsp_dt->screen_h / 2 + (*height) / 2;
	if (dsp_dt->spr.endy >= dsp_dt->screen_h)
		dsp_dt->spr.endy = dsp_dt->screen_h - 1;
}

static void	get_sprite_width(int *width, t_data *dsp_dt)
{
	(dsp_dt->spr.screenx) = (int)((dsp_dt->screen_w / 2)
			* (1 + dsp_dt->spr.dir_x / dsp_dt->spr.dir_y));
	(*width) = abs((int)(dsp_dt->screen_h / dsp_dt->spr.dir_y));
	dsp_dt->spr.startx = (dsp_dt->spr.screenx) - (*width) / 2;
	if (dsp_dt->spr.startx < 0)
		dsp_dt->spr.startx = 0;
	dsp_dt->spr.endx = (dsp_dt->spr.screenx) + (*width) / 2;
	if (dsp_dt->spr.endx >= dsp_dt->screen_w)
		dsp_dt->spr.endx = dsp_dt->screen_w - 1;
}

void	sprites(int **buffer, t_data *dsp_dt)
{
	int	y;
	int	height;
	int	width;

	get_sprites_dist(dsp_dt);
	y = 0;
	while (y < dsp_dt->spr.tot)
	{
		get_sprite_values(y, dsp_dt);
		get_sprite_height(&height, dsp_dt);
		get_sprite_width(&width, dsp_dt);
		draw_sprites(width, height, buffer, dsp_dt);
		y++;
	}
}
