/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:47:40 by cvarela-          #+#    #+#             */
/*   Updated: 2024/11/18 09:47:41 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_pow(int n, int pot)
{
	if (pot == 0)
		return (1);
	else if (pot == 1)
		return (n);
	else if (pot < 0)
		return (-1);
	else
		return (n * ft_pow(n, --pot));
}
