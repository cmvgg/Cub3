/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:01:26 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/28 16:34:34 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free(double **split)
{
	int	limit;

	limit = 0;
	if (split)
	{
		while (limit <= 7 && split[limit] != NULL)
		{
			free(split[limit]);
			split[limit] = NULL;
			limit++;
		}
		free(split);
		split = NULL;
	}
	return ;
}
