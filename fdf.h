/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 00:14:32 by lwang             #+#    #+#             */
/*   Updated: 2017/01/06 13:44:48 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./minilibx_macos/mlx.h"
#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_event
{
	void *mlx;
	void *win;
	int len_m; // max of len in the map
	int line_m; // max line of the map
	int fd;
	char *pixel_array_img;
	void *img;
	int bits_per_pixel;
	int size_line;
	int endian;
}				t_event;

typedef struct s_point
{
	int x;
	int y;
	int z;
}				t_point;

#endif
