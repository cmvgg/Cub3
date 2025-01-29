/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:01:26 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/29 14:00:00 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

void	ft_free(double **split)
{
	int	limit;
	int	i;

	limit = 0;
	i = 1;
	if (split)
	{
		while (i >= 0 && limit <= 1 && split[i][limit])
		{
			free(split[limit]);
			split[limit] = NULL;
			limit++;
		}
		free(split);
	}
	return ;
}
