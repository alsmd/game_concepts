/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:50:05 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 19:06:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine.h"

void	add_obj(t_engine *eng)
{
	eng->new_obj = new_obj(0, 0, 0, 0);
	eng->new_obj->vertices = 0;
	eng->new_obj->next = 0;
	change_parent(eng->new_obj, &eng->global);
	eng->is_creating = 1;
	printf("CREATING OBJ\n");
	fflush(stdout);
}

void	save_obj(t_engine *eng)
{
	t_obj	*begin;

	begin = eng->on_scene;
	while (begin && begin->next)
		begin = begin->next;
	if (!begin)
		eng->on_scene = eng->new_obj;
	else
		begin->next = eng->new_obj;
	eng->new_obj = 0;
	eng->is_creating = 0;
	printf("Object was created\n");
	fflush(stdout);
}





void	render_objs(t_engine *eng)
{
	t_obj *begin;

	begin = eng->on_scene;
	while (begin)
	{
		//fill(, 0x0000ff, e&ng->vars);
		print_vertices(begin->vertices, eng);
		begin = begin->next;
	}
}