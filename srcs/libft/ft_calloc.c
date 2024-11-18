/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:45:44 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:45:48 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			amt;
	size_t			i;

	amt = count * size;
	ptr = malloc(amt);
	if (!ptr)
		return (0);
	i = 0;
	while (i < amt)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
