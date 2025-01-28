/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:49:53 by cvarela-          #+#    #+#             */
/*   Updated: 2025/01/28 18:19:44 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

static int	gnl_find_eof(char **res, char **line)
{
	*line = ft_strdup(*res);
	free(*res);
	*res = NULL;
	return (0);
}

static int	gnl_find_nl(char **res, char **line)
{
	char	*temp_1;
	char	*temp_2;
	char	*newline_pos;

	newline_pos = ft_strchr(*res, '\n');
	if (!newline_pos)
		return (free(res), -1);
	*newline_pos = '\0';
	*line = ft_strdup(*res);
	temp_1 = *res;
	temp_2 = ft_strdup(newline_pos + 1);
	free(temp_1);
	*res = temp_2;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*res;
	char		*temp;
	char		buff[BUFFER_SIZE + 1];
	int			num;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (0);
	if (!res)
		res = ft_strdup("");
	while (!ft_strchr(res, '\n'))
	{
		num = read(fd, buff, BUFFER_SIZE);
		if (num <= 0)
			break ;
		buff[num] = '\0';
		temp = res;
		res = ft_strjoin(temp, buff);
		free(temp);
	}
	if (ft_strchr(res, '\n'))
		return (gnl_find_nl(&res, line));
	if (num == 0)
		return (gnl_find_eof(&res, line));
	free(res);
	return (0);
}
