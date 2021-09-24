/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 09:34:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
t_vars	vars;

void	put_pixel(t_vec point, int color)
{
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

typedef struct s_axis
{
	t_vec	up;
	t_vec	right;
}	t_axis;

typedef struct s_obj
{
	t_vec	position;
	t_axis	axis;
}	t_obj;

float	angle;
float	precision = 0.9f;

void	set_axis(t_obj *obj)
{
	vec_init(&obj->axis.up, 0, 1);
	vec_init(&obj->axis.right, 1, 0);
}
int red = 0xff0000;
int green = 0x00ff00;
int blue = 0x0000ff;

void	draw_axis(t_obj obj, t_vars *vars)
{
	vec_scale(&obj.axis.up, 50);
	vec_scale(&obj.axis.right, 50);
	vec_sum(&obj.axis.up, &obj.position);
	vec_sum(&obj.axis.right, &obj.position);
	drawline(obj.axis.up, obj.position, green, vars);
	drawline(obj.axis.right, obj.position, red, vars);
}


void	is_looking_at(t_obj obj, t_vec point)
{
	t_vec	obj_to_point;
	float	is_looking_at;

	vec_init(&obj_to_point, point.x - obj.position.x, point.y - obj.position.y);
	vec_magnitude(&obj_to_point);
	vec_normalize(&obj_to_point);
	is_looking_at = vec_dot_product(&obj_to_point, &obj.axis.right);
	if (is_looking_at >= precision)
		red = blue;
	else
		red = 0xff00000;
}
float	x = 0;
float	y = 0;
int	update(t_vars *vars)
{
	t_obj	dot;
	t_vec	point;
	t_vec	center;
	

	vec_init(&center, WIDTH / 2, HEIGHT / 2);
	//clean screen
	mlx_clear_window(vars->mlx, vars->win);
	//initial position of our object
	vec_init(&dot.position, 0, 0);
	//Point that will be checked if the object is looking at it
	vec_init(&point, -150, 20);
	//The center of the world will be the middle of screen
	vec_sum(&dot.position, &center);
	vec_sum(&point, &center);
	//set initial axis
	set_axis(&dot);
	//rotate axis
	vec_rotate(&dot.axis.up, angle);
	vec_rotate(&dot.axis.right, angle);
	//is obj looking at point
	is_looking_at(dot, point);
	//scale axis and put in the right place to vizualization
	draw_axis(dot, vars);
	put_pixel(point, red);
	return (1);
}

int	key(int keycode, void *v)
{
	const int	left = 65361;
	const int	right = 65363;
	const int	up = 65362;
	const int	down = 65364;
	const float	speed = 2;

	if (keycode == left)
		angle -= speed;
	if (keycode == right)
		angle += speed;
	//printf("%d\n", keycode);
	//fflush(stdout);
}

int main(void)
{
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key, 0);
    mlx_loop(vars.mlx);
    return (0);
}
