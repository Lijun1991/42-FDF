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

// void	draw_point(int x, int y, t_info *e)
// {
// 	int i;
// 	int color;
	
// 	color = 0xFFFFFF;
// 	i = x * e->bits_per_pixel / 8 + y * e->size_line;
// 	e->pixel_array_img[i] = color;
// 	e->pixel_array_img[++i] = color >> 8;
// 	e->pixel_array_img[++i] = color >> 16;
// }

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
		mlx_pixel_put(e->mlx, e->win, x + 120, y + 180, 0x00FFFFFF);
		// draw_point(x, y, e);
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

int expose_hook(t_info *e)
{
	// e->img = mlx_new_image(e->mlx, img_x, img_y);
	// e->pixel_array_img = mlx_get_data_addr(e->img, &(e->bits_per_pixel), &(e->size_line), &(e->endian));
	draw_map(e);
	// mlx_put_image_to_window(e->mlx, e->win, e->img, img_win_x, img_win_y);
	
	// ft_bzero(e->pixel_array_img, img_x * 4 + img_y * e->size_line);
	 // mlx_destroy_image(e->win, e->img);
	return (0);
}

void	get_window(t_info *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, win_x, win_y, "42");
}

