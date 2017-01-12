/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:07:23 by lwang             #+#    #+#             */
/*   Updated: 2017/01/10 15:18:56 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int expose_hook(t_event *e)
{
	int i;

	i = 100;
	while (i < 200)
	{
		mlx_pixel_put(e->mlx, e->win, i, 100, 0x00FFFFFF);
		i++;
	}
	return (0);
}

 int main()
{
	t_event *e;
	int fd;
	char *line;

	e = (t_event*)malloc(sizeof(t_event));
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, 1000, 1200, "42");
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
