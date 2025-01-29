/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:01:26 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/29 16:13:13 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/cub3d.h"
#include <stdio.h>

void	ft_free(double **split)
{
	t_map_data	*map;
	int			limit;
	int			i;

	map = get_map_data();
	limit = 1;
	i = map->sprite -1;
	if (split)
	{
		while (i > 0)
		{
			while (limit >= 0 && split[i][limit])
			{
				free(split[limit]);
				split[limit] = NULL;
				limit++;
			}
			free(split);
			split = NULL;
			split++;
			i--;
		}
		free(split);
	}
	return ;
}
