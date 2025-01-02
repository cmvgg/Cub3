/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderframe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2024/12/28 13:58:31 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_ray(int x, t_data *dsp_dt)
{
	double	camx;

	camx = 2 * x / (double)dsp_dt->screen_w - 1;
	dsp_dt->ray.dir_x = dsp_dt->ply.dir_x + dsp_dt->ply.plnx * camx;
	dsp_dt->ray.dir_y = dsp_dt->ply.dir_y + dsp_dt->ply.plny * camx;
	dsp_dt->ray.ddistx = fabs(1 / dsp_dt->ray.dir_x);
	dsp_dt->ray.ddisty = fabs(1 / dsp_dt->ray.dir_y);
}

static void	dist_to_wall(t_data *dsp)
{
	dsp->map.x = (int)dsp->ply.posx;
	dsp->map.y = (int)dsp->ply.posy;
	if (dsp->ray.dir_x < 0)
	{
		dsp->ray.stepx = -1;
		dsp->ray.sdistx = (dsp->ply.posx - dsp->map.x) * dsp->ray.ddistx;
	}
	else
	{
		dsp->ray.stepx = 1;
		dsp->ray.sdistx = (dsp->map.x + 1.0 - dsp->ply.posx) * dsp->ray.ddistx;
	}
	if (dsp->ray.dir_y < 0)
	{
		dsp->ray.stepy = -1;
		dsp->ray.sdisty = (dsp->ply.posy - dsp->map.y) * dsp->ray.ddisty;
	}
	else
	{
		dsp->ray.stepy = 1;
		dsp->ray.sdisty = (dsp->map.y + 1.0 - dsp->ply.posy) * dsp->ray.ddisty;
	}
}

static void	dda_algorithm(t_data *dsp_dt)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dsp_dt->ray.sdistx < dsp_dt->ray.sdisty)
		{
			dsp_dt->ray.sdistx += dsp_dt->ray.ddistx;
			dsp_dt->map.x += dsp_dt->ray.stepx;
			dsp_dt->map.side = 0;
		}
		else
		{
			dsp_dt->ray.sdisty += dsp_dt->ray.ddisty;
			dsp_dt->map.y += dsp_dt->ray.stepy;
			dsp_dt->map.side = 1;
		}
		if (dsp_dt->map.board[dsp_dt->map.y][dsp_dt->map.x] == '1')
			hit = 1;
	}
}

static void	find_height_line(int **buffer, int x, t_data *dsp_dt)
{
	if (dsp_dt->map.side == 0)
	{
		dsp_dt->ray.wall_dist = (dsp_dt->map.x - dsp_dt->ply.posx
				+ (1 - dsp_dt->ray.stepx) / 2);
		dsp_dt->ray.wall_dist /= dsp_dt->ray.dir_x;
	}
	else
	{
		dsp_dt->ray.wall_dist = (dsp_dt->map.y - dsp_dt->ply.posy
				+ (1 - dsp_dt->ray.stepy) / 2);
		dsp_dt->ray.wall_dist /= dsp_dt->ray.dir_y;
	}
	dsp_dt->ray.lineh = (int)(dsp_dt->screen_h / dsp_dt->ray.wall_dist);
	dsp_dt->spr.starty = dsp_dt->screen_h / 2 - dsp_dt->ray.lineh / 2;
	if (dsp_dt->spr.starty < 0)
		(dsp_dt->spr.starty) = 0;
	dsp_dt->spr.endy = dsp_dt->screen_h / 2 + dsp_dt->ray.lineh / 2;
	if (dsp_dt->spr.endy >= dsp_dt->screen_h)
		dsp_dt->spr.endy = dsp_dt->screen_h - 1;
	buff_no_wall(x, buffer, dsp_dt);
	find_tex_x(dsp_dt);
	find_tex_pos(dsp_dt);
	buff_wall(x, buffer, dsp_dt);
}

int	render_frame(t_data *dsp)
{
	int	x;
	int	**buffer;

	x = 0;
	init_buffer(1, &buffer, dsp);
	update_player_movement(dsp);
	while (x < dsp->screen_w)
	{
		set_ray(x, dsp);
		dist_to_wall(dsp);
		dda_algorithm(dsp);
		find_height_line(buffer, x, dsp);
		dsp->spr.zbuf[x] = dsp->ray.wall_dist;
		x++;
	}
	sprites(buffer, dsp);
	draw_buffer(buffer, dsp);
	init_buffer(0, &buffer, dsp);
    bonus_draw_minimap(dsp);
	mlx_put_image_to_window(dsp->mlx.mlx, dsp->mlx.win, dsp->mlx.img, 0, 0);
	mlx_do_sync(dsp->mlx.mlx);
	return (0);
}
