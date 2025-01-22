/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:49:01 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/22 10:18:39 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_t;
	unsigned char	*s2_t;
	size_t			count;

	count = 0;
	s1_t = (unsigned char *)s1;
	s2_t = (unsigned char *)s2;
	while (count <= n && s1_t[count] && s2_t[count])
	{
		if (s1_t[count] != s2_t[count])
			return (s1_t[count] - s2_t[count]);
		count++;
	}
	if (count < n)
		return (s1_t[count] - s2_t[count]);
	return (0);
}
