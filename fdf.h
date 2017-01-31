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

# define win_x 2000
# define win_y 1600

# define img_x 2100
# define img_y 1700

# define img_win_x 120
# define img_win_y 180

# define move_up -100
# define move_down 100
# define move_left -100
# define move_right 100

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
	int fd;
	int map_length; 
	double *line_length;
	double **z_h;
	t_point	*p_center;

	char *pixel_array_img;
	void *img;

	int bits_per_pixel;
	int size_line;
	int endian;
}				t_info;

typedef struct  s_matrix
{
	double a1;
	double a2;
	double a3;
	double b1;
	double b2;
	double b3;
	double c1;
	double c2;
	double c3;
}				t_matrix;

/* 
get_info.c
*/
t_point	**get_line(char **s, int j, t_info *e);
t_point	***get_map(t_info *e);
double	get_max_line_len(t_info *e);
void	get_center(t_info *e);
void	get_map_length(t_info *e, char *file);

/* 
draw.c
*/
void	draw_line(t_point *a, t_point *b, t_info *e);
void	draw_map (t_info *e);
void	get_window(t_info *e);
int		expose_hook(t_info *e);

/* 
hook.c
*/
int key_hook(int keycode, t_info *e);
int expose_hook(t_info *e);

/* 
matrix_map.c
*/
t_matrix *math_trsnlation_matrix(void);
t_matrix *math_x_rotation(void);
t_matrix *math_y_rotation(void);
t_matrix *math_z_rotation(void);
void	matrix_points_p_center(t_point *p, t_matrix *m, t_info *e);
void	matrix_map(t_info *e, t_matrix *m);
void	cal_rotation(t_info *e, char axis);

#endif
