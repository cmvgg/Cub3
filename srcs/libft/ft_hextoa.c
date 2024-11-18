/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:46:15 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:46:18 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	len_num(unsigned long n, int base)
{
	unsigned long	len;

	len = 0;
	while (n)
	{
		len++;
		n /= base;
	}
	return (len);
}

static void	hex_to_pos(unsigned long n, char **str)
{
	unsigned long	len;
	unsigned long	num;

	num = n;
	len = len_num(num, 16);
	if (n == 0)
		len = 1;
	(*str) = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*str))
		(*str) = NULL;
	(*str)[len--] = '\0';
	while (len > 0)
	{
		if (n % 16 <= 9)
			(*str)[len--] = (n % 16) + '0';
		else
			(*str)[len--] = (n % 16) + '7';
		n /= 16;
	}
	if (n <= 9)
		(*str)[len] = n + '0';
	else
		(*str)[len] = n + '7';
}

char	*ft_hextoa(unsigned long n, char **str)
{
	hex_to_pos(n, str);
	return (*str);
}
