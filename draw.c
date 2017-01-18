/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:34:22 by lwang             #+#    #+#             */
/*   Updated: 2017/01/11 14:34:24 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(int x, int y, t_info *e)
{
	int i;
	int color;
	
	color = 0x00FFFFFF;
	i = x * e->bits_per_pixel / 8 + y * e->size_line;
	e->pixel_array_img[i] = color;
}

void	draw_line(t_point *a, t_point *b, t_info *e)
{
	int x = a->x;
	int y = a->y;
	#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
	int dx = fabs(b->x - a->x);
	int dy = fabs(b->y - a->y);
	int s1 = sign(b->x - a->x);
	int s2 = sign(b->y - a->y);
	int swap = 0;
	if (dy > dx)
	{
		int tmp = dx;
		dx = dy;
		dy = tmp;
		swap = 1;
	}
	int D = 2 * dy - dx;
	for (int i = 0; i < dx; i++)
	{
		// mlx_pixel_put(e->mlx, e->win, x + 250, y + 150, 0x00FFFFFF);
		draw_point(x, y, e);
		while (D >= 0)
		{
			D = D - 2 * dx;
			if (swap)
				x += s1;
			else
				y += s2;
		}
		D = D + 2 * dy;
		if (swap)
			y += s2;
		else
			x += s1;
	}
}

void	draw_map (t_info *e)
{
	int j;
	int i;

	j = 0;
	while (e->map[j] != NULL)
	{
		i = 0;
		while (e->map[j][i]->x != -1)
		{
			if (e->map[j][i + 1]->x != -1)
			{
				draw_line(e->map[j][i], e->map[j][i + 1], e);
				//printf("hen(%f, %f), (%f, %f)\n", e->map[j][i]->x, e->map[j][i]->y, e->map[j][i + 1]->x, e->map[j][i + 1]->y);
			}
			if (e->map[j + 1] != NULL)
			{
				draw_line(e->map[j][i], e->map[j + 1][i], e);
				//printf("zong(%f, %f), (%f, %f)\n", e->map[j][i]->x, e->map[j][i]->y, e->map[j + 1][i]->x, e->map[j + 1][i]->y);
			}
			i++;
		}
		j++;
	}
}

void	get_window(t_info *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, win_x, win_y, "42");
}

