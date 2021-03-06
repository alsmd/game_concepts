/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_kit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:02:52 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 17:53:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_kit.h"



t_vec	get_parent_scope(t_obj obj)
{
	t_vec	new_pos;
	t_obj	parent;

	parent = *obj.parent;
	vec_init(&new_pos, obj.position.x, obj.position.y, obj.position.z);
	vec_scale(&parent.axis.right, new_pos.x);
	vec_scale(&parent.axis.up, new_pos.y);
	vec_scale(&parent.axis.center, new_pos.z);
	new_pos.x = parent.axis.up.x	+ parent.axis.right.x + parent.axis.center.x;
	new_pos.y = parent.axis.up.y	+ parent.axis.right.y +  parent.axis.center.y;
	new_pos.z = parent.axis.up.z	+ parent.axis.right.z +  parent.axis.center.z;
	return (new_pos);
}

t_vec	get_global_scope(t_obj obj)
{
	t_vec	new_pos;
	t_vec	parent;

	if (obj.is_global)
		return (obj.position);
	new_pos = get_parent_scope(obj);
	parent = get_global_scope(*obj.parent);
	vec_sum(&new_pos, &parent);
	return (new_pos);
}

void	print_axis(t_obj obj, int scale, t_engine *eng)
{
	t_axis	axis;
	t_vec	global_position;

	axis = obj.axis;
	vec_scale(&axis.up, scale);
	vec_scale(&axis.right, scale);
	vec_scale(&axis.center, scale);
	vec_scale(&axis.up, axis.scale);
	vec_scale(&axis.right, axis.scale);
	vec_scale(&axis.center, axis.scale);
	global_position = get_global_scope(obj);
	vec_sum(&axis.up, &global_position);
	vec_sum(&axis.right, &global_position);
	vec_sum(&axis.center, &global_position);
	drawline(axis.up, global_position, 0x00ff00, &eng->vars, &eng->screen);
	drawline(axis.right, global_position, 0xff0000, &eng->vars, &eng->screen);
	drawline(axis.center, global_position, 0x0000ff, &eng->vars, &eng->screen);
}

static void	set_axis(t_obj *obj)
{
	vec_init(&obj->axis.up, 0, 1, 0);
	vec_init(&obj->axis.right, 1, 0, 0);
	vec_init(&obj->axis.center, 0, 0, 1);
}

void	init_obj(t_obj *obj, t_obj *parent, float x, float y, float z)
{
	if (parent == 0)
		obj->is_global = 1;
	else
		obj->is_global = 0;
	obj->parent = parent;
	vec_init(&obj->position, x, y, z);
	set_axis(obj);
}

t_vec	vec_distance(t_vec	from, t_vec to)
{
	t_vec	dis;

	dis.x = to.x - from.x;
	dis.y = to.y - from.y;
	return (dis);
}

void	change_parent(t_obj *obj, t_obj *parent)
{
	t_obj	p;
	t_vec	parent_to_obj;

	p = *parent;
	p.position = get_global_scope(p);
	obj->position = get_global_scope(*obj);
	parent_to_obj = vec_distance(p.position, obj->position);
	obj->position = parent_to_obj;
	obj->parent = parent;
}

t_obj	*new_obj(t_obj *parent, float x, float y, float z)
{
	t_obj	*obj;

	obj = (t_obj *) calloc(1, sizeof(t_obj));
	if (parent == 0)
		obj->is_global = 1;
	else
		obj->is_global = 0;
	obj->parent = parent;
	vec_init(&obj->position, x, y, z);
	set_axis(obj);
	return (obj);
}

void	rotatex_axis(t_axis *axis, float angle)
{
	vec_rotatex(&axis->center, angle);
	vec_rotatex(&axis->up, angle);
	vec_rotatex(&axis->right, angle);
}

void	rotatey_axis(t_axis *axis, float angle)
{
	vec_rotatey(&axis->center, angle);
	vec_rotatey(&axis->up, angle);
	vec_rotatey(&axis->right, angle);
}

void	rotatez_axis(t_axis *axis, float angle)
{
	vec_rotatez(&axis->center, angle);
	vec_rotatez(&axis->up, angle);
	vec_rotatez(&axis->right, angle);
}