/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:39 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:50:40 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(double rot, t_data *dsp_dt)
{
	double	olddir_x;
	double	oldplnx;
	double	tmp;

	olddir_x = dsp_dt->ply.dir_x;
	dsp_dt->ply.dir_x = dsp_dt->ply.dir_x * cos(rot)
		- dsp_dt->ply.dir_y * sin(rot);
	dsp_dt->ply.dir_y = olddir_x * sin(rot) + dsp_dt->ply.dir_y * cos(rot);
	tmp = dsp_dt->ply.dir_x;
	dsp_dt->ply.lirx = dsp_dt->ply.dir_y;
	dsp_dt->ply.liry = -tmp;
	oldplnx = dsp_dt->ply.plnx;
	dsp_dt->ply.plnx = dsp_dt->ply.plnx * cos(rot)
		- dsp_dt->ply.plny * sin(rot);
	dsp_dt->ply.plny = oldplnx * sin(rot) + dsp_dt->ply.plny * cos(rot);
}

void	rot_right(double rot, t_data *dsp_dt)
{
	rotate(-rot, dsp_dt);
}

void	rot_left(double rot, t_data *dsp_dt)
{
	rotate(rot, dsp_dt);
}
