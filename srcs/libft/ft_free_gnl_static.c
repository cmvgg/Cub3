/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_gnl_static.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:20:28 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/29 11:24:22 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_free_gnl_static(void)
{
	static char	*res = NULL;

	if (res)
	{
		free(res);
		res = NULL;
	}
}
