/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2025/01/24 18:01:16 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

static int	bonus_mouse_move(int x, int y, t_data *dsp_dt)
{
	int		center_x;
	double	rot_speed;

	center_x = dsp_dt->screen_w / 2;
	rot_speed = 0.003 * (x - center_x);
	if (x != center_x)
	{
		if (x > center_x)
			rot_left(rot_speed, dsp_dt);
		else if (x < center_x)
			rot_right(-rot_speed, dsp_dt);
		mlx_mouse_move(dsp_dt->mlx.mlx, dsp_dt->mlx.win, center_x,
			dsp_dt->screen_h / 2);
	}
	(void)y;
	return (0);
}


void	bonus_init_mouse(t_data *dsp_dt)
{
	mlx_mouse_hide(dsp_dt->mlx.mlx, dsp_dt->mlx.win);
	mlx_mouse_move(dsp_dt->mlx.mlx, dsp_dt->mlx.win, (int)(dsp_dt->screen_w
			/ 2), (int)(dsp_dt->screen_h / 2));
	mlx_hook(dsp_dt->mlx.win, MotionNotify, PointerMotionMask, bonus_mouse_move,
		dsp_dt);
}
#else

void	bonus_init_mouse(t_data *dsp_dt)
{
	(void)dsp_dt;
}
#endif