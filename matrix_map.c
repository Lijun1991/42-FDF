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

void	math_matrix(t_matrix *m)
{
	m->a1 = 1;
	m->a2 = 0;
	m->a3 = 0;
	m->b1 = 0;
	m->b2 = 1;
	m->b3 = 0;
	m->c1 = 0;
	m->c2 = 0;
	m->c3 = 1;
}

void	math_z_rotation(t_matrix *m)
{
	m->a1 = cos(degree);
	m->a2 = sin(degree);
	m->a3 = 0;
	m->b1 = sin(degree);
	m->b2 = -cos(degree);
	m->b3 = 0;
	m->c1 = 0;
	m->c2 = 0;
	m->c3 = 1;
}

void	math_y_rotation(t_matrix *m)
{
	m->a1 = cos(degree);
	m->a2 = 0;
	m->a3 = -sin(degree);
	m->b1 = 0;
	m->b2 = 1;
	m->b3 = 0;
	m->c1 = sin(degree);
	m->c2 = 0;
	m->c3 = cos(degree);
}

void	math_x_rotation(t_matrix *m)
{
	m->a1 = 1;
	m->a2 = 0;
	m->a3 = 0;
	m->b1 = 0;
	m->b2 = cos(degree);
	m->b3 = sin(degree);
	m->c1 = 0;
	m->c2 = -sin(degree);
	m->c3 = cos(degree);
}

t_matrix	*hook_rotation(t_matrix)
{
	if ()
}

/*
matrice all the point base on p as the center for rotation
*/
void	matrix_points_p_center(t_point *p, t_info *e)
{
	t_point *tmp;
	t_matrix *m;
	m = (t_matrix*)malloc(sizeof(t_matrix) * 1);
	m = math_matrix(m);
	tmp = (t_point*)malloc(sizeof(t_point) * 1);
	p->x -= e->p_center->x;
	p->y -= e->p_center->y;
	tmp->x = p->x * m->a1 + p->y * m->a2 + p->z * m->a3;
	tmp->y = p->x * m->b1 + p->y * m->b2 + p->z * m->b3;
	tmp->z = p->x * m->c1 + p->y * m->c2 + p->z * m->c3;
	p->x += e->p_center->x;
	p->y += e->p_center->y;
}

void	matrix_map(t_info *e)
{
	int i;
	int j;

	j = 0;
	while (e->map[j] != NULL)
	{
		i = 0;
		while(e->map[j][i]->x != -1)
		{
			matrix_points_p_center(e->map[j][i], e);
			i++;
		}
		j++;
	}
}









