/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:07:23 by lwang             #+#    #+#             */
/*   Updated: 2017/01/13 10:45:10 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int expose_hook(t_info *e)
// {
// 	int i;

// 	i = 100;
// 	while (i < 200)
// 	{
// 		mlx_pixel_put(e->mlx, e->win, i, 100, 0x00FFFFFF);
// 		i++;
// 	}
// 	return (0);
// }

void	draw_point(int x, int y, t_info *e)
{
	int i;
	int color;
	
	// color = 0x00FF5000;
	i = x * 4 + y * e->size_line;
	e->pixel_array_img[i] = 0x00;
	e->pixel_array_img[++i] = 0xFF;
	e->pixel_array_img[++i] = 0x47;
	// e->pixel_array_img[++i] = 0x00;
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
		//mlx_pixel_put(e->mlx, e->win, x, y, 0x00FFFFFF);
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

int key_hook(int keycode, t_info *e) 
{
	if (keycode == 53)
	{
	// 	 mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}


 int main()
{
	t_info *e;
	int fd;
	char *line;
	t_point *a;
	t_point *b;

	e = (t_info*)malloc(sizeof(t_info));
	a = (t_point*)malloc(sizeof(t_point));
	b = (t_point*)malloc(sizeof(t_point));
	a->x = 20;
	a->y = 30;
	a->z = 0;
	b->x = 290;
	b->y = 180;
	b->z = 0;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, 1000, 1200, "42");

	e->img = mlx_new_image(e->mlx, 100, 100);
	e->pixel_array_img = mlx_get_data_addr(e->img, &(e->bits_per_pixel), &(e->size_line), &(e->endian));
	// mlx_expose_hook(e->win, expose_hook, e);
	mlx_pixel_put(e->mlx, e->win, 20, 30, 0x00FFFF00);
	mlx_pixel_put(e->mlx, e->win, 290, 180, 0x00FFFF00);
	draw_line(a, b, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 20, 30);

	mlx_destroy_image(e->win, e->img);
	mlx_key_hook(e->win, key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}







