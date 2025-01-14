/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findspr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:51:51 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/14 13:49:43 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	swap_values(double *index, double *find)
{
	int	tmp;

	tmp = *index;
	*index = *find;
	*find = tmp;
}

static void	init_sprites(t_data *dsp_dt, t_map_data *map_data)
{
	int	y;
	int	x;
	int	z;

	y = 0;
	x = 0;
	z = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (dsp_dt->map.board[y][x] == '2')
			{
				dsp_dt->spr.buf[z] = (double *)ft_calloc(sizeof(double), 2);
				dsp_dt->spr.buf[z][0] = y + 0.5;
				dsp_dt->spr.buf[z][1] = x + 0.5;
				z++;
			}
			x++;
		}
		y++;
	}
}

void	find_sprites(t_data *dsp_dt, t_map_data *map_data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	dsp_dt->spr.tot = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (dsp_dt->map.board[y][x] == '2')
				dsp_dt->spr.tot++;
			x++;
		}
		y++;
	}
	dsp_dt->spr.zbuf = (double *)ft_calloc(sizeof(double), dsp_dt->screen_w);
	dsp_dt->spr.dist = (double *)ft_calloc(sizeof(double), dsp_dt->spr.tot);
	dsp_dt->spr.buf = (double **)ft_calloc(sizeof(double *), dsp_dt->spr.tot);
	dsp_dt->spr.order = (double *)ft_calloc(sizeof(double), dsp_dt->spr.tot);
	init_sprites(dsp_dt, map_data);
}

void	sort_sprites(double *order, double *dist, int tot, int index)
{
	int		pos;
	double	men_dis;
	int		find;

	pos = 0;
	men_dis = 0;
	find = 0;
	while (++index < tot)
	{
		pos = index;
		find = index;
		men_dis = dist[index];
		while (++pos < tot)
		{
			if (dist[pos] > men_dis)
			{
				find = pos;
				men_dis = dist[pos];
			}
		}
		if (men_dis != dist[index])
			swap_values(&order[index], &order[find]);
		if (men_dis != dist[index])
			swap_values(&dist[index], &dist[find]);
	}
}
