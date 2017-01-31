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

double	get_z_max(t_info *e)
{
	int i;
	int j;
	double max_z;

	max_z = 0;
	j = 0;
	while (e->map[j] != NULL)
	{
		i = 0;
		while(e->map[j][i]->x != -1)
		{
			if(e->map[j][i]->z > max_z)
				max_z = e->map[j][i]->z;
			i++;
		}
		j++;
	}
	return (max_z);
}

void	get_map_length(t_info *e, char *file)
{
	int fd;
	char *line;
	int len;

	len = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
		len++;
	e->map_length = len;
	close(fd);
}

double	get_max_line_len(t_info *e)
{
	int i;
	double max_len;

	i = 0;
	max_len = 0;
	while (i < e->map_length)
	{
		if (e->line_length[i] > max_len)
			max_len = e->line_length[i];
		i++;
	}
	//printf("max_len is %f\n", max_len);
	return (max_len - 1);
}

void	get_center(t_info *e)
{
	t_point *center;

	center = (t_point*)malloc(sizeof(t_point) * 1);
	center->x = get_max_line_len(e) / 2 * 40;
	center->y = e->map_length / 2 * 40;
	center->z = get_z_max(e) / 2 * 40;
	e->p_center = center;
	//printf("%f, %f, %f\n", center->x, center->y, center->z);
}

t_point	**get_line(char **s, int j, t_info *e)
{
	t_point **line;
	int i;

	i = 0;
	while (s[i])
		i++;
	e->line_length[j] = i;
	e->z_h[j] = (double*)malloc(sizeof(double) * i);
	line = (t_point**)malloc(sizeof(t_point*) * (i + 1));
	i = 0;
	while (s[i])
	{
		line[i] = (t_point*)malloc(sizeof(t_point));
		line[i]->x = i * 40;
		line[i]->y = j * 40;
		line[i]->z = ft_atoi(s[i]) * 20;
		e->z_h[j][i] = line[i]->z;
		//printf("(%f, %f, %f)\n", line[i]->x, line[i]->y,line[i]->z);
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
	e->z_h = (double**)malloc(sizeof(double*) * e->map_length);
	e->line_length = (double*)malloc(sizeof(double) * e->map_length);
	if (!(map = (t_point***)malloc(sizeof(t_point**) * (e->map_length + 1))))
		return (0);
	while (get_next_line(e->fd, &line))
	{
		map[j] = get_line(ft_strsplit(line, ' '), j, e);
		j++;
	}
	map[j] = NULL;
	// int z = 0;
	// while(z < e->map_length)
	// {
	// 	printf("%d\n", e->line_length[z]);
	// 	z++;
	// }
	return (map);
}