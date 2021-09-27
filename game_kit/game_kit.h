/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_kit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 19:05:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_KIT_H
#define GAME_KIT_H
#include <stdio.h>
#include <stdlib.h>
#include "../vec_lib/vec.h"
#define LEFT_CLICK 1
#define RIGHT_CLICK 3
#define SPACE_KEY 32
#define ENTER_KEY 65293
#define A_KEY 97
#define D_KEY 100
#define S_KEY 115
#define W_KEY 119
#define LEFT_KEY 65361
#define RIGHT_KEY 65363
#define UP_KEY 65362
#define DOWN_KEY 65364
#define ESQ_KEY 65307

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endin;
	int		w;
	int		h;
}	t_data;

typedef struct s_axis
{
	t_vec	up;
	t_vec	right;
	t_vec	center;
	float	scale;
}	t_axis;


typedef struct s_obj
{
	t_vec			position;
	t_vec			*vertices;
	struct s_obj	*parent;
	t_axis			axis;
	int				is_global;
	struct s_obj	*next;
	t_vec			angle;
}	t_obj;

typedef	struct s_engine
{
	t_obj	global;
	t_obj	*on_scene;
	t_vars	vars;
	t_data	screen;
	t_obj	*new_obj;
	t_vec	new_vertice;
	int		is_creating;
}	t_engine;

t_vec	get_parent_scope(t_obj obj);
t_vec	get_global_scope(t_obj obj);
t_obj	*new_obj(t_obj *parent, float x, float y, float z);
void	print_axis(t_obj obj, int scale, t_engine *eng);
void	init_obj(t_obj *obj, t_obj *parent, float x, float y, float z);
void	change_parent(t_obj *obj, t_obj *parent);
void	drawline(t_vec vec1, t_vec vec2, int color, t_vars *vars, t_data *img);
void	rotatex_axis(t_axis *axis, float angle);
void	rotatey_axis(t_axis *axis, float angle);
void	rotatez_axis(t_axis *axis, float angle);

#endif