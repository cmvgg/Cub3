#include "../includes/cub3d.h"

static void	find_color(int tex_y, char **color, t_data *dsp_dt)
{
	if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x > 0)
	{
		tex_y = (int)dsp_dt->tex.tex_pos & (dsp_dt->eas.height - 1);
		(*color) = dsp_dt->eas.addr + (tex_y * dsp_dt->eas.length);
		(*color) += (dsp_dt->tex.tex_x * (dsp_dt->eas.bpp / 8));
	}
	else if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x < 0)
	{
		tex_y = (int)dsp_dt->tex.tex_pos & (dsp_dt->wes.height - 1);
		(*color) = dsp_dt->wes.addr + (tex_y * dsp_dt->wes.length);
		(*color) += (dsp_dt->tex.tex_x * (dsp_dt->wes.bpp / 8));
	}
	else if (dsp_dt->map.side == 1 && dsp_dt->ray.dir_y > 0)
	{
		tex_y = (int)dsp_dt->tex.tex_pos & (dsp_dt->sou.height - 1);
		(*color) = dsp_dt->sou.addr + (tex_y * dsp_dt->sou.length);
		(*color) += (dsp_dt->tex.tex_x * (dsp_dt->sou.bpp / 8));
	}
	else
	{
		tex_y = (int)dsp_dt->tex.tex_pos & (dsp_dt->nor.height - 1);
		(*color) = dsp_dt->nor.addr + (tex_y * dsp_dt->nor.length);
		(*color) += (dsp_dt->tex.tex_x * (dsp_dt->nor.bpp / 8));
	}
}

void	buff_no_wall(int x, int **buffer, t_data *dsp_dt)
{
	int	count;

	count = 0;
	while (count < dsp_dt->screen_h)
	{
		if (count < dsp_dt->spr.starty)
			buffer[count][x] = dsp_dt->map.sky;
		else if (count >= dsp_dt->spr.endy)
			buffer[count][x] = dsp_dt->map.floor;
		count++;
	}
}

void	find_tex_x(t_data *dsp_dt)
{
	int	tex_pos;

	if (dsp_dt->map.side == 0)
		dsp_dt->tex.wall_x = dsp_dt->ply.posy + dsp_dt->ray.wall_dist
			* dsp_dt->ray.dir_y;
	else
		dsp_dt->tex.wall_x = dsp_dt->ply.posx + dsp_dt->ray.wall_dist
			* dsp_dt->ray.dir_x;
	dsp_dt->tex.wall_x -= floor(dsp_dt->tex.wall_x);
	if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x >= 0)
	{
		tex_pos = (int)(dsp_dt->tex.wall_x * (double)dsp_dt->eas.width);
		tex_pos = dsp_dt->eas.width - tex_pos - 1;
	}
	else if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x < 0)
		tex_pos = (int)(dsp_dt->tex.wall_x * (double)dsp_dt->wes.width);
	else if (dsp_dt->map.side == 1 && dsp_dt->ray.dir_y >= 0)
		tex_pos = (int)(dsp_dt->tex.wall_x * (double)dsp_dt->sou.width);
	else
	{
		tex_pos = (int)(dsp_dt->tex.wall_x * (double)dsp_dt->nor.width);
		tex_pos = dsp_dt->nor.width - tex_pos - 1;
	}
	dsp_dt->tex.tex_x = tex_pos;
}

void	find_tex_pos(t_data *dsp_dt)
{
	double	step;
	double	tex_pos;

	if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x >= 0)
		step = 1.0 * dsp_dt->eas.height / dsp_dt->ray.lineh;
	else if (dsp_dt->map.side == 0 && dsp_dt->ray.dir_x < 0)
		step = 1.0 * dsp_dt->wes.height / dsp_dt->ray.lineh;
	else if (dsp_dt->map.side == 1 && dsp_dt->ray.dir_y >= 0)
		step = 1.0 * dsp_dt->sou.height / dsp_dt->ray.lineh;
	else
		step = 1.0 * dsp_dt->nor.height / dsp_dt->ray.lineh;
	tex_pos = (dsp_dt->spr.starty - dsp_dt->screen_h / 2 + dsp_dt->ray.lineh
			/ 2) * step;
	dsp_dt->tex.step = step;
	dsp_dt->tex.tex_pos = tex_pos;
}

void	buff_wall(int x, int **buffer, t_data *dsp_dt)
{
	char	*color;
	int		tex_y;
	int		y;

	y = 0;
	tex_y = 0;
	color = NULL;
	y = dsp_dt->spr.starty;
	while (y < dsp_dt->spr.endy)
	{
		find_color(tex_y, &color, dsp_dt);
		buffer[y][x] = *(unsigned int *)color;
		dsp_dt->tex.tex_pos += dsp_dt->tex.step;
		y++;
	}
}
