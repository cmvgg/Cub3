/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:52:00 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:52:01 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_data *dsp_dt)
{
	if (keycode == 65307)
	{
		printf("Cub3D cerrado con exito");
		printf("\n\n");
		exit(0);
	}
	else if (keycode == 119)
		dsp_dt->key.move_up = 1;
	else if (keycode == 115)
		dsp_dt->key.move_down = 1;
	else if (keycode == 97)
		dsp_dt->key.move_left = 1;
	else if (keycode == 100)
		dsp_dt->key.move_right = 1;
	else if (keycode == 65363)
		dsp_dt->key.rot_right = 1;
	else if (keycode == 65361)
		dsp_dt->key.rot_left = 1;
	return (0);
}

int	key_release(int keycode, t_data *dsp_dt)
{
	if (keycode == 119)
		dsp_dt->key.move_up = 0;
	else if (keycode == 115)
		dsp_dt->key.move_down = 0;
	else if (keycode == 97)
		dsp_dt->key.move_left = 0;
	else if (keycode == 100)
		dsp_dt->key.move_right = 0;
	else if (keycode == 65363)
		dsp_dt->key.rot_right = 0;
	else if (keycode == 65361)
		dsp_dt->key.rot_left = 0;
	return (0);
}
