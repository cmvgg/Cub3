#include "../includes/cub3d.h"

static void	set_north_dir(t_data *dsp_dt)
{
	double	tmp;

	dsp_dt->ply.dir_x = 0;
	dsp_dt->ply.dir_y = -1;
	tmp = dsp_dt->ply.dir_x;
	dsp_dt->ply.lirx = dsp_dt->ply.dir_y;
	dsp_dt->ply.liry = -tmp;
	dsp_dt->ply.plnx = 0.66;
	dsp_dt->ply.plny = 0;
}

static void	set_south_dir(t_data *dsp_dt)
{
	double	tmp;

	dsp_dt->ply.dir_x = 0;
	dsp_dt->ply.dir_y = 1;
	tmp = dsp_dt->ply.dir_x;
	dsp_dt->ply.lirx = dsp_dt->ply.dir_y;
	dsp_dt->ply.liry = -tmp;
	dsp_dt->ply.plnx = -0.66;
	dsp_dt->ply.plny = 0;
}

static void	set_east_dir(t_data *dsp_dt)
{
	double	tmp;

	dsp_dt->ply.dir_x = 1;
	dsp_dt->ply.dir_y = 0;
	tmp = dsp_dt->ply.dir_x;
	dsp_dt->ply.lirx = dsp_dt->ply.dir_y;
	dsp_dt->ply.liry = -tmp;
	dsp_dt->ply.plnx = 0;
	dsp_dt->ply.plny = 0.66;
}

static void	set_west_dir(t_data *dsp_dt)
{
	double	tmp;

	dsp_dt->ply.dir_x = -1;
	dsp_dt->ply.dir_y = 0;
	tmp = dsp_dt->ply.dir_x;
	dsp_dt->ply.lirx = dsp_dt->ply.dir_y;
	dsp_dt->ply.liry = -tmp;
	dsp_dt->ply.plnx = 0;
	dsp_dt->ply.plny = -0.66;
}

void	set_dir(char c, t_data *dsp_dt)
{
	if (c == 'N')
		set_north_dir(dsp_dt);
	else if (c == 'S')
		set_south_dir(dsp_dt);
	else if (c == 'W')
		set_west_dir(dsp_dt);
	else if (c == 'E')
		set_east_dir(dsp_dt);
}
