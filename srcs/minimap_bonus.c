/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2025/01/16 09:58:05 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	bonus_draw_minimap(t_data *dsp)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = -1;
	while (++y < dsp->map.height - 1)
	{
		x = -1;
		while (++x < dsp->map.width)
		{
			if (dsp->map.board[y][x] == '1' || dsp->map.board[y][x] == '2')
			{
				i = 0;
				while (i < MINIMAP_SCALE)
				{
					j = 0;
					while (j < MINIMAP_SCALE)
						my_mlx_pixel_put(dsp, x * MINIMAP_SCALE + i, y
							* MINIMAP_SCALE + j++, 0xFFFFFF);
					i++;
				}
			}
		}
	}
}

void	bonus_draw_minimap_player(t_data *dsp)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			my_mlx_pixel_put(dsp, dsp->ply.posx * MINIMAP_SCALE + i,
				dsp->ply.posy * MINIMAP_SCALE + j, 0xFF0000);
			j++;
		}
		i++;
	}
}
#else

void	bonus_draw_minimap(t_data *dsp)
{
	(void)dsp;
}
void	bonus_draw_minimap_player(t_data *dsp)
{
	(void)dsp;
}
#endif