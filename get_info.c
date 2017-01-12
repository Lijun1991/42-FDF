/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:25:59 by lwang             #+#    #+#             */
/*   Updated: 2017/01/11 14:26:01 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**get_line(char **s, int j)
{
	t_point **line;
	int i;

	i = 0;
	while (s[i])
		i++;
	line = (t_point**)malloc(sizeof(t_point*) * (i + 1));
	i = 0;
	while (s[i])
	{
		line[i] = (t_point*)malloc(sizeof(t_point));
		line[i]->x = i * 40;
		line[i]->y = j * 40;
		line[i]->z = ft_atoi(s[i]);
		//printf("%d (%f, %f, %f)\n", i, line[i]->x, line[i]->y, line[i]->z);
		i++;
	}
    line[i] = (t_point*)malloc(sizeof(t_point));
	line[i]->x = -1;
	line[i]->y = -1;
	line[i]->z = -1;
	return (line);
}

t_point	***get_map(t_info *e)
{
	int j;  // index for the length of the map
	char *line;
	t_point ***map;


	j = 0;
	map = (t_point***)malloc(sizeof(t_point**) * (e->map_length + 1));
	while (get_next_line(e->fd, &line))
	{
		map[j] = get_line(ft_strsplit(line, ' '), j);
		j++;
	}
	map[j] = NULL;
	return (map);
}