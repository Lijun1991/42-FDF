/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:38:17 by lwang             #+#    #+#             */
/*   Updated: 2017/01/11 14:38:20 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int mouse_hook(int button, int x, int y, t_info *e)
{
	printf("mouse : %d (%d:%d)\n", button, x, y);
	return (0);
}

// mlx_mouse_hook(e.win, mouse_hook, &e);

*/

int key_hook(int keycode, t_info *e) 
{
	if (keycode == 53)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}
