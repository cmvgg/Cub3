/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:47:10 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:47:11 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			count;

	count = 0;
	temp = (unsigned char *)s;
	while (count < n)
	{
		if (temp[count] == (unsigned char)c)
			return (temp + count);
		count++;
	}
	return (0);
}
