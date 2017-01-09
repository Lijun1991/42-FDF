/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:32:21 by lwang             #+#    #+#             */
/*   Updated: 2017/01/06 23:09:41 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	draw(void *mlx, void *win)
{
	int x;
	int y;
	
	y = 100;
	while (y < 300)
	{
		x = 100;
		mlx_pixel_put(mlx, win, x, y, 0x00FFFFFF);
		y++;
	}
}

int mouse_hook(int button, int x, int y, t_event *e)
{
	printf("mouse : %d (%d:%d)\n", button, x, y);
	return (0);
}

*/


int key_hook(int keycode, t_event *e) 
{
	if (keycode == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}

t_point	*get_point(char **s, int j, t_event *e)
{
	t_point *dst;
	int i;
	int m;

	i = 0;
	m = 0;
	while (s[i])
		i++;
	if (i > m)
		m = i;
	dst = (t_point*)malloc(sizeof(t_point) * (i + 1));
	i = 0;
	while (s[i])
	{
		dst[i].x = i;
		dst[i].y = j;
		dst[i].z = ft_atoi(s[i]);
	//	printf("%d (%d, %d, %d)\n", i, dst[i].x, dst[i].y, dst[i].z);
		i++;
	}
	dst[i].x = -1;
	dst[i].y = -1;
	dst[i].z = -1;
	e->len_m = i;
	return (dst);
}

t_point	**get_map(t_event *e)
{
	int j;
	char *line;
	t_point **dst;

	j = 0;
	dst = (t_point**)malloc(sizeof(t_point*) * (e->line_m + 1));
	while (get_next_line(e->fd, &line))
	{
		dst[j] = get_point(ft_strsplit(line, ' '), j, e);
		j++;
	}
	dst[j] = NULL;
	//printf("%d, %d, %d\n", dst[2][2].x, dst[2][2].y, dst[2][2].z);
	return (dst);
}

void	draw_point(int x, int y, t_event *e)
{
	int i;
	int color;
	
	color = 0x00FFFFFF;
	i = x * 4 + y * e->size_line;
	e->pixel_array_img[i] = (char)color;
}

void	draw_line(t_point a, t_point b, t_event *e)
{
	void *img;
	int x;
	int y;
	double dx;
	double dy;
	int swap;
	int tmp;
	double D;
	double s1;
	double s2;

	tmp = 0;
	D = 0;
	img = mlx_new_image(e->mlx, e->len_m, e->line_m);
	#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))
	x = a.x;
	y = a.y;
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	s1 = sign(b.x - a.x);
	s2 = sign(b.y - a.y);
	swap = 0;
	if (dy > dx)
	{
		tmp = dx;
		dx = dy;
		dy = tmp;
		swap = 1;
	}
	D = 2 * dy - dx;
	for (double i = 0; i < dx; i++)
	{
	//	mlx_pixel_put(e->mlx, e->win, x * 10, y * e->line_m, 0x00FFFFFF);
		draw_point(x*10, y*10, e);
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

void	draw_map (t_event *e)
{
	t_point **map;
	int j;
	int i;
	int m;
	int n;

	m = 0;
	n = 0;
	map = get_map(e);
	j = 0;
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i].x != -1)
		{
			m = i + 1;
			n = j + 1;
			if (map[j][m].x != -1)
				draw_line(map[j][i], map[j][m], e);
			if (map[n] != NULL)
				draw_line(map[j][i], map[n][i], e);
			i++;
		}
		j++;
	}
}


int expose_hook(t_event *e)
{
//	draw(e->mlx, e->win);
	e->img = mlx_new_image(e->mlx, 800, 700);
	e->pixel_array_img = mlx_get_data_addr(e->img, &(e->bits_per_pixel), &(e->size_line), &(e->endian));
	draw_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 50, 50);
	return (0);
}



int main(int ac, char **av)
{
	t_event e;
	int fd;
	(void)ac;
	char *line;

	e.line_m = 0;
	fd = open(av[1], O_RDONLY);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, 1000, 1200, "42");
	mlx_key_hook(e.win, key_hook, &e);
	// mlx_mouse_hook(e.win, mouse_hook, &e);
	while (get_next_line(fd, &line))
		e.line_m++;
	close(fd);
	fd = open(av[1], O_RDONLY);
	e.fd = fd;
//	draw_map(fd, size, &e)

	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}












