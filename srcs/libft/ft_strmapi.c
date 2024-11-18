/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:48:55 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:48:56 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		count;

	count = 0;
	if (!s)
		return (0);
	while (s[count])
		count++;
	result = (char *)malloc((count + 1) * sizeof(char));
	if (!result)
		return (0);
	result[count] = '\0';
	while (count > 0)
	{
		count--;
		result[count] = (*f)(count, s[count]);
	}
	return (result);
}
