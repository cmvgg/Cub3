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
	z = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (dsp_dt->map.board[y][x] == '2')
			{
				dsp_dt->spr.buf[z] = (double *)malloc(sizeof(double) * 2);
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
	dsp_dt->spr.zbuf = (double *)malloc(sizeof(double) * dsp_dt->screen_w);
	dsp_dt->spr.dist = (double *)malloc(sizeof(double) * dsp_dt->spr.tot);
	dsp_dt->spr.buf = (double **)malloc(sizeof(double *) * dsp_dt->spr.tot);
	dsp_dt->spr.order = (double *)malloc(sizeof(double) * dsp_dt->spr.tot);
	init_sprites(dsp_dt, map_data);
}

void	sort_sprites(double *order, double *dist, int tot)
{
	int		index;
	int		pos;
	int		find;
	double	men_dis;

	index = 0;
	while (index < tot)
	{
		pos = index + 1;
		find = index;
		men_dis = dist[index];
		while (pos < tot)
		{
			if (dist[pos] > men_dis)
				find = pos;
			if (dist[pos] > men_dis)
				men_dis = dist[pos];
			pos++;
		}
		if (men_dis != dist[index])
			swap_values(&order[index], &order[find]);
		if (men_dis != dist[index])
			swap_values(&dist[index], &dist[find]);
		index++;
	}
}
