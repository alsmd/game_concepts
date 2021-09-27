/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:51:34 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 19:13:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine.h"

void	add_vertice(t_engine *eng)
{
	t_vec	*begin;
	t_vec	tmp;
	t_vec	*vec;

	vec = new_vec(eng->new_vertice.x, eng->new_vertice.y, eng->new_vertice.z);
	change_value(&eng->new_vertice, -1, -1, -1);
	begin = eng->new_obj->vertices;
	vec->next = 0;
	while (begin && begin->next)
		begin = begin->next;
	if (!begin)
		eng->new_obj->vertices = vec;
	else
		begin->next = vec;
	printf("New point add to the obj: \n");
	printf("x %f\n", vec->x);
	printf("y %f\n", vec->y);
	printf("z %f\n", vec->z);
	fflush(stdout);
}

static int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

void fill(t_vec vec1, t_vec vec2, t_vec vec3,  int color, t_engine *eng)
{
	t_vec	d_vec1;
    int		steps;

	d_vec1.x = vec2.x - vec1.x;
	d_vec1.y = vec2.y - vec1.y;
	
	steps = take_step(d_vec1.x, d_vec1.y);
	d_vec1.x /= steps;
	d_vec1.y /= steps;

	while (steps--)
	{
		drawline(vec1, vec3, color, &eng->vars, &eng->screen);
		vec_sum(&vec1, &d_vec1);
	}
}

void	print_vertices(t_vec *vertice, t_engine *eng)
{
	t_vec	proj[3];
	t_vec	*begin;
	int		index;

	index = 0;
	begin = vertice;
	while (begin)
	{
		proj[index] = *begin;
		proj_vec(&proj[index], eng);
		vec_sum(&proj[index], &eng->global.position);
		if (index == 2)
		{
			fill(proj[0], proj[1], proj[2], 0x0000f0, eng);
			index = 0;
		}
		else
			index++;
		begin = begin->next;
	}

}


void	proj_vec(t_vec *vec, t_engine *eng)
{
	t_axis	axis;

	axis = eng->global.axis;
	vec_scale(&axis.center, vec->z);
	vec_scale(&axis.right, vec->x);
	vec_scale(&axis.up, vec->y);
	vec_scale(&axis.center, eng->global.axis.scale);
	vec_scale(&axis.right,eng->global.axis.scale);
	vec_scale(&axis.up, eng->global.axis.scale);
	vec->x = axis.center.x + axis.up.x + axis.right.x;
	vec->y = axis.center.y + axis.up.y + axis.right.y;
	vec->z = axis.center.z + axis.up.z + axis.right.z;
}

void	cord_to_vertice(int cord, t_engine *eng)
{
	if (eng->new_vertice.x == -1)
	{
		eng->new_vertice.x = cord;
		printf("x is now: %d\n", cord);
		fflush(stdout);
	}
	else if (eng->new_vertice.y == -1)
	{
		eng->new_vertice.y = cord;
		printf("y is now: %d\n", cord);
		fflush(stdout);
	}
	else if (eng->new_vertice.z == -1)
	{
		eng->new_vertice.z = cord;
		printf("z is now: %d\n", cord);
		fflush(stdout);
		add_vertice(eng);
		if (has_three_ver(eng))
			save_obj(eng);
	}
	
}

int	has_three_ver(t_engine *eng)
{
	t_vec	*begin;
	int		index;

	index = 0;
	begin = eng->new_obj->vertices;
	while (begin)
	{
		begin = begin->next;
		index++;
	}
	if (index >= 3)
		return (1);
	return (0);
}