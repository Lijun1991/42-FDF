/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 00:14:32 by lwang             #+#    #+#             */
/*   Updated: 2017/01/11 14:20:17 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./minilibx_macos/mlx.h"
#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_point
{
    double x;
   	double y;
    double z;
}				t_point;

typedef struct	s_info
{
	void *mlx;
	void *win;

	t_point ***map;
	int map_length; 
	int line_length;

	int fd;

	char *pixel_array_img;
	void *img;

	int bits_per_pixel;
	int size_line;
	int endian;
}				t_info;

/* 
get_info.c
*/
t_point	**get_line(char **s, int j);
t_point	***get_map(t_info *e);

/* 
draw.c
*/
void	draw_line(t_point *a, t_point *b, t_info *e);
void	draw_map (t_info *e);
void	get_window(t_info *e);

/* 
hook.c
*/
int key_hook(int keycode, t_info *e);

#endif
