/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:40:34 by ivromero          #+#    #+#             */
/*   Updated: 2025/01/24 17:10:40 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef BONUS

void	check_and_draw_pixel(t_data *dsp, t_coords c)
{
	if (c.map_x >= 0 && c.map_x < dsp->map.width && c.map_y >= 0
		&& c.map_y < dsp->map.height)
	{
		if (dsp->map.board[c.map_y][c.map_x] == '1')
			my_mlx_pixel_put(dsp, c.real_x, c.real_y, 0xFFFFFF);
		else if (dsp->map.board[c.map_y][c.map_x] == '0')
			my_mlx_pixel_put(dsp, c.real_x, c.real_y, 0x000000);
		else if (dsp->map.board[c.map_y][c.map_x] == '2')
			my_mlx_pixel_put(dsp, c.real_x, c.real_y, 0x00BB00);
	}
}

void	bonus_draw_minimap(t_data *dsp)
{
	int			x;
	int			y;
	t_coords	c;

	y = 0;

	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			c.map_x = (int)(dsp->ply.posx - MINIMAP_SIZE / (2 * MINIMAP_SCALE)
					+ x / MINIMAP_SCALE);
			c.map_y = (int)(dsp->ply.posy - MINIMAP_SIZE / (2 * MINIMAP_SCALE)
					+ y / MINIMAP_SCALE);
			c.real_x = MINIMAP_START_X + x;
			c.real_y = MINIMAP_START_Y + y;
			check_and_draw_pixel(dsp, c);
			x++;
		}
		y++;
	}
}

void	bonus_draw_minimap_player(t_data *dsp)
{
	int	player_radius;
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	player_radius = MINIMAP_SCALE / 2;
	center_x = 10 + 100 / 2 + MINIMAP_SCALE / 2;
	center_y = 10 + 100 / 2 + MINIMAP_SCALE / 2;
	i = -player_radius;
	while (i <= player_radius)
	{
		j = -player_radius;
		while (j <= player_radius)
		{
			if (i * i + j * j <= player_radius * player_radius)
				my_mlx_pixel_put(dsp, center_x + i, center_y + j, 0xFF0000);
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