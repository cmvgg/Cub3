/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:52 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/12 23:59:02 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *dsp_dt, int x, int y, int color)
{
	char	*dst;

	dst = dsp_dt->mlx.addr + (y * dsp_dt->mlx.length) + (x * (dsp_dt->mlx.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	init_buffer(int mode, int ***buffer, t_data *dsp_dt)
{
	int	x;

	if (mode == 1)
	{
		x = 0;
		(*buffer) = (int **)ft_calloc(sizeof(int *), dsp_dt->screen_h);
		while (x < dsp_dt->screen_h)
		{
			(*buffer)[x] = (int *)ft_calloc(sizeof(int), dsp_dt->screen_w);
			x++;
		}
	}
	else if (mode == 0)
	{
		x = 0;
		while (x < dsp_dt->screen_h)
			free((*buffer)[x++]);
		free(*buffer);
	}
}

void	draw_buffer(int **buffer, t_data *dsp_dt)
{
	int	count_y;
	int	count_x;

	count_y = 0;
	while (count_y < dsp_dt->screen_h)
	{
		count_x = 0;
		while (count_x < dsp_dt->screen_w)
		{
			my_mlx_pixel_put(dsp_dt, count_x, count_y,
				buffer[count_y][count_x]);
			count_x++;
		}
		count_y++;
	}
}
