/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_kit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 08:50:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_KIT_H
#define GAME_KIT_H
#include <stdio.h>
#include <stdlib.h>
#include "../vec_lib/vec.h"

typedef struct s_axis
{
	t_vec	up;
	t_vec	right;
	t_vec	center;
}	t_axis;

typedef struct s_obj
{
	t_vec			position;
	struct s_obj	*parent;
	t_axis			axis;
	int				is_global;
}	t_obj;

t_vec	get_parent_scope(t_obj obj);
t_vec	get_global_scope(t_obj obj);
void	print_axis(t_obj obj, int scale, void (*drawline)(t_vec, t_vec, int, void *), void *aux);
void	init_obj(t_obj *obj, t_obj *parent, float x, float y, float z);
void	change_parent(t_obj *obj, t_obj *parent);

#endif