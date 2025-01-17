/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2025/01/17 17:58:13 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	bonus_print_minimap(int x, int y, t_data *dsp)
{
	int	i;
	int	j;
				if ((dsp->map.board[y][x] == '1' || dsp->map.board[y][x] == '2')
			&& ((x <= (dsp->ply.posx + 4) && x >= (dsp->ply.posx - 4))
			&& (y <= (dsp->ply.posy + 4) && y >= (dsp->ply.posy - 4))))
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

void	bonus_draw_minimap(t_data *dsp)
{
	int	x;
	int	y;


	y = -1;
	while (++y < dsp->map.height - 1)
	{
		x = -1;
		while (++x < dsp->map.width)
		{
			bonus_print_minimap(x, y, dsp);
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