/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2024/12/28 18:50:57 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS
void	bonus_draw_minimap(t_data *dsp)
{
	int	map_x;
	int	map_y;
	int	scale;
	int	color;
	int	i;
	int	j;
	int	px;
	int	py;

	scale = 10;
	map_y = 0;
	while (map_y < dsp->map.height)
	{
		map_x = 0;
		while (map_x < dsp->map.width)
		{
			if (dsp->map.board[map_y][map_x] == '1')
			{
				color = 0xFFFFFF;
				i = 0;
				while (i < scale)
				{
					j = 0;
					while (j < scale)
					{
						my_mlx_pixel_put(dsp, map_x * scale + i, map_y * scale
							+ j, color);
						j++;
					}
					i++;
				}
			}
			map_x++;
		}
		map_y++;
	}
	px = dsp->ply.posx * scale;
	py = dsp->ply.posy * scale;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			my_mlx_pixel_put(dsp, px + i, py + j, 0xFF0000);
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
#endif