/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:32:21 by lwang             #+#    #+#             */
/*   Updated: 2017/01/11 14:21:12 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int expose_hook(t_info *e)
{
	e->img = mlx_new_image(e->mlx, 1000, 800);
	e->pixel_array_img = mlx_get_data_addr(e->img, &(e->bits_per_pixel), &(e->size_line), &(e->endian));
	draw_map(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, img_win_x, img_win_y);
	return (0);
}

int main(int ac, char **av)
{
	t_info *e;
	int fd;
	(void)ac;

	if (!(e = (t_info*)malloc(sizeof(t_info))))
	{
		ft_putstr("malloc error");
		return (0);
	}
	get_map_length(e, av[1]);
	fd = open(av[1], O_RDONLY);
	e->fd = fd;
	/* get all info from the file for drawing*/
	e->map = get_map(e);

	get_center(e);

	matrix_map(e);

	get_window(e);

	mlx_expose_hook(e->win, expose_hook, e);
	
	mlx_key_hook(e->win, key_hook, &e);
	// draw_map(e);

	mlx_loop(e->mlx);
	return (0);
}
