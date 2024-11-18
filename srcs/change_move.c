/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:50:26 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:50:27 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	adv_move(double move, t_data *dsp_dt)
{
	if (dsp_dt->map.board[(int)dsp_dt->ply.posy]
		[(int)(dsp_dt->ply.posx + dsp_dt->ply.dir_x * move)] == '0')
		dsp_dt->ply.posx += dsp_dt->ply.dir_x * move;
	if (dsp_dt->map.board[(int)(dsp_dt->ply.posy + dsp_dt->ply.dir_y * move)]
		[(int)dsp_dt->ply.posx] == '0')
		dsp_dt->ply.posy += dsp_dt->ply.dir_y * move;
}

void	back_move(double move, t_data *dsp_dt)
{
	if (dsp_dt->map.board[(int)dsp_dt->ply.posy]
		[(int)(dsp_dt->ply.posx - dsp_dt->ply.dir_x * move)] == '0')
		dsp_dt->ply.posx -= dsp_dt->ply.dir_x * move;
	if (dsp_dt->map.board[(int)(dsp_dt->ply.posy - dsp_dt->ply.dir_y * move)]
		[(int)dsp_dt->ply.posx] == '0')
		dsp_dt->ply.posy -= dsp_dt->ply.dir_y * move;
}

void	dsp_left(double move, t_data *dsp_dt)
{
	if (dsp_dt->map.board[(int)dsp_dt->ply.posy]
		[(int)(dsp_dt->ply.posx + dsp_dt->ply.lirx * move)] == '0')
		dsp_dt->ply.posx += dsp_dt->ply.lirx * move;
	if (dsp_dt->map.board[(int)(dsp_dt->ply.posy + dsp_dt->ply.liry * move)]
		[(int)dsp_dt->ply.posx] == '0')
		dsp_dt->ply.posy += dsp_dt->ply.liry * move;
}

void	dsp_right(double move, t_data *dsp_dt)
{
	if (dsp_dt->map.board[(int)dsp_dt->ply.posy]
		[(int)(dsp_dt->ply.posx - dsp_dt->ply.lirx * move)] == '0')
		dsp_dt->ply.posx -= dsp_dt->ply.lirx * move;
	if (dsp_dt->map.board[(int)(dsp_dt->ply.posy - dsp_dt->ply.liry * move)]
		[(int)dsp_dt->ply.posx] == '0')
		dsp_dt->ply.posy -= dsp_dt->ply.liry * move;
}

void	update_player_movement(t_data *dsp_dt)
{
	double	space_mov;
	double	space_rot;

	space_mov = 0.1;
	space_rot = -0.05;
	if (dsp_dt->key.move_up)
		adv_move(space_mov, dsp_dt);
	if (dsp_dt->key.move_down)
		back_move(space_mov, dsp_dt);
	if (dsp_dt->key.move_left)
		dsp_left(space_mov, dsp_dt);
	if (dsp_dt->key.move_right)
		dsp_right(space_mov, dsp_dt);
	if (dsp_dt->key.rot_right)
		rot_right(space_rot, dsp_dt);
	if (dsp_dt->key.rot_left)
		rot_left(space_rot, dsp_dt);
}
