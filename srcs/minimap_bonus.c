/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.c>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2025/01/12 19:19:34 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	bonus_draw_minimap(t_data *dsp)
{
	int	map_x;
	int	map_y;
	int	i;
	int	j;

	map_y = -1;
	while (++map_y < dsp->map.height)
	{
		map_x = -1;
		while (++map_x < dsp->map.width)
		{
			if (dsp->map.board[map_y][map_x] == '1')
			{
				i = 0;
				while (i < MINIMAP_SCALE)
				{
					j = 0;
					while (j < MINIMAP_SCALE)
						my_mlx_pixel_put(dsp, map_x * MINIMAP_SCALE + i, map_y
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
#endif