/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/02 23:44:51 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	north_texture(t_data *dsp_dt)
{
	int	count;
	int	verif;

	count = ft_strlen(dsp_dt->nor.path) - 3;
	verif = ft_strncmp(dsp_dt->nor.path + count, "xpm", count);
	if (verif == 0)
		dsp_dt->nor.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->nor.path, &dsp_dt->nor.width, &dsp_dt->nor.height);
	else
		dsp_dt->nor.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->nor.path, &dsp_dt->nor.width, &dsp_dt->nor.height);
	dsp_dt->nor.addr = mlx_get_data_addr(dsp_dt->nor.img, &dsp_dt->nor.bpp,
			&dsp_dt->nor.length, &dsp_dt->nor.endian);
}

void	south_texture(t_data *dsp_dt)
{
	int	count;
	int	verif;

	count = ft_strlen(dsp_dt->sou.path) - 3;
	verif = ft_strncmp(dsp_dt->sou.path + count, "xpm", 3);
	if (verif == 0)
		dsp_dt->sou.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->sou.path, &dsp_dt->sou.width, &dsp_dt->sou.height);
	else
		dsp_dt->sou.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->sou.path, &dsp_dt->sou.width, &dsp_dt->sou.height);
	dsp_dt->sou.addr = mlx_get_data_addr(dsp_dt->sou.img, &dsp_dt->sou.bpp,
			&dsp_dt->sou.length, &dsp_dt->sou.endian);
}

void	east_texture(t_data *dsp_dt)
{
	int	count;
	int	verif;

	count = ft_strlen(dsp_dt->eas.path) - 3;
	verif = ft_strncmp(dsp_dt->eas.path + count, "xpm", 3);
	if (verif == 0)
		dsp_dt->eas.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->eas.path, &dsp_dt->eas.width, &dsp_dt->eas.height);
	else
		dsp_dt->eas.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->eas.path, &dsp_dt->eas.width, &dsp_dt->eas.height);
	dsp_dt->eas.addr = mlx_get_data_addr(dsp_dt->eas.img, &dsp_dt->eas.bpp,
			&dsp_dt->eas.length, &dsp_dt->eas.endian);
}

void	west_texture(t_data *dsp_dt)
{
	int	count;
	int	verif;

	count = ft_strlen(dsp_dt->wes.path) - 3;
	verif = ft_strncmp(dsp_dt->wes.path + count, "xpm", 3);
	if (verif == 0)
		dsp_dt->wes.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->wes.path, &dsp_dt->wes.width, &dsp_dt->wes.height);
	else
		dsp_dt->wes.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->wes.path, &dsp_dt->wes.width, &dsp_dt->wes.height);
	dsp_dt->wes.addr = mlx_get_data_addr(dsp_dt->wes.img, &dsp_dt->wes.bpp,
			&dsp_dt->wes.length, &dsp_dt->wes.endian);
}

void	sprite_texture(t_data *dsp_dt)
{
	int	count;
	int	verif;

	count = ft_strlen(dsp_dt->spr.path) - 3;
	verif = ft_strncmp(dsp_dt->spr.path + count, "xpm", 3);
	if (verif == 0)
		dsp_dt->spr.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->spr.path, &dsp_dt->spr.width, &dsp_dt->spr.height);
	else
		dsp_dt->spr.img = mlx_xpm_file_to_image(dsp_dt->mlx.mlx,
				dsp_dt->spr.path, &dsp_dt->spr.width, &dsp_dt->spr.height);
	dsp_dt->spr.addr = mlx_get_data_addr(dsp_dt->spr.img, &dsp_dt->spr.bpp,
			&dsp_dt->spr.length, &dsp_dt->spr.endian);
}
