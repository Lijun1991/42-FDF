/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 20:31:27 by lwang             #+#    #+#             */
/*   Updated: 2017/01/13 20:31:29 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix *math_trsnlation_matrix(void)
{
	t_matrix *m;
	m = (t_matrix*)malloc(sizeof(t_matrix) * 1);
	m->a1 = 1;
	m->a2 = 0;
	m->a3 = 0;
	m->b1 = 0;
	m->b2 = 1;
	m->b3 = 0;
	m->c1 = 0;
	m->c2 = 0;
	m->c3 = 1;
	return (m);
}

t_matrix *math_z_rotation(void)
{
	t_matrix *m;
	m = (t_matrix*)malloc(sizeof(t_matrix) * 1);
	m->a1 = cos(M_PI / 60);
	m->a2 = sin(M_PI / 60);
	m->a3 = 0;
	m->b1 = -sin(M_PI / 60);
	m->b2 = cos(M_PI / 60);
	m->b3 = 0;
	m->c1 = 0;
	m->c2 = 0;
	m->c3 = 1;
	return (m);
}

t_matrix *math_y_rotation(void)
{
	t_matrix *m;
	m = (t_matrix*)malloc(sizeof(t_matrix) * 1);
	m->a1 = cos(M_PI / 60);
	m->a2 = 0;
	m->a3 = -sin(M_PI / 60);
	m->b1 = 0;
	m->b2 = 1;
	m->b3 = 0;
	m->c1 = sin(M_PI / 60);
	m->c2 = 0;
	m->c3 = cos(M_PI / 60);
	return (m);
}

t_matrix *math_x_rotation(void)
{
	t_matrix *m;
	m = (t_matrix*)malloc(sizeof(t_matrix) * 1);
	m->a1 = 1;
	m->a2 = 0;
	m->a3 = 0;
	m->b1 = 0;           
	m->b2 = cos(M_PI / 60);
	m->b3 = sin(M_PI / 60);
	m->c1 = 0;
	m->c2 = -sin(M_PI / 60);
	m->c3 = cos(M_PI / 60);
	return (m);
}

void		cal_rotation(t_info *e, char axis)
{
	t_matrix *m;

	if (axis == 'z')
		m = math_z_rotation();
	else if (axis == 'y')
		m = math_y_rotation();
	else
		m = math_x_rotation();
	matrix_map(e, m);
	free(m);
}

/*
matrice all the point base on p as the center for rotation
*/
void	matrix_points_p_center(t_point *p, t_matrix *m, t_info *e)
{
	double tmp_x;
	double tmp_y;
	double tmp_z;

	p->x -= e->p_center->x;
	p->y -= e->p_center->y;
	tmp_x = p->x * m->a1 + p->y * m->a2 + p->z * m->a3;
	tmp_y = p->x * m->b1 + p->y * m->b2 + p->z * m->b3;
	tmp_z = p->x * m->c1 + p->y * m->c2 + p->z * m->c3;
	p->z = tmp_z;
	p->y = tmp_y;
	p->x = tmp_x;
	p->x += e->p_center->x;
	p->y += e->p_center->y;
	// printf("p is (%f, %f, %f)\n", p->x, p->y, p->z);
}

void	matrix_map(t_info *e, t_matrix *m)
{
	int i;
	int j;

	j = 0;
	while (e->map[j] != NULL)
	{
		i = 0;
		while(e->map[j][i]->x != -1)
		{
			matrix_points_p_center(e->map[j][i], m, e);
			i++;
		}
		j++;
	}
}









