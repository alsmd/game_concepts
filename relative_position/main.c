/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/23 19:29:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
t_vars	vars;

void	put_pixel(t_vec point, int color)
{
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

void	rotate(t_vec *vec, float	angle)
{
	float	rad;
	float	x;
	float	y;

	x = vec->x;
	y = vec->y;
	rad = angle * M_PI / 100;
	
	vec->x = x * cos(rad) - y * sin(rad);
	vec->y = y * cos(rad) + x * sin(rad);
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

void	set_axis(t_obj *obj)
{
	vec_init(&obj->axis.up, 0, 1);
	vec_init(&obj->axis.right, 1, 0);
}
#define red 0xff0000
#define green 0x00ff00
#define blue 0x0000ff

void	draw_relative_point(t_obj obj, t_vec point)
{
	t_axis	axis;

	//right é a direção no qual o x do axis do objeto esta apontando
	//top é a direção no qual o y do axis do objeto esta apontando
	axis = obj.axis;
	//eu pego a verdadeira cordenada considerando a direção que os axis estão apontando
	scale(&axis.right, point.x);
 	scale(&axis.up, point.y);
	sum(&axis.right, &axis.up);
	point = axis.right;
	//faço isso ser relativo a origem do mundo novamente
	sum(&point, &obj.position);
	//draw
	put_pixel(point, blue);
}

float	x = 0;
float	y = 0;
int	update(t_vars *vars)
{
	t_obj	dot;
	t_vec	point;
	t_axis	axis;
	t_vec	center;
	

	vec_init(&center, WIDTH / 2, HEIGHT / 2);
	//clean screen
	mlx_clear_window(vars->mlx, vars->win);

	//initial position of our object
	vec_init(&dot.position, 0, 0);
	sum(&dot.position, &center);
	//our dotte that will be relative our object
	vec_init(&point, 20, 20);

	//set initial axis
	set_axis(&dot);
	//rotate axis
	rotate(&dot.axis.up, angle);
	rotate(&dot.axis.right, angle);
	//cpy axis to not modify the real one
	axis = dot.axis;

	//scale axis and put in the right place to vizualization
	scale(&axis.up, 50);
	scale(&axis.right, 50);
	sum(&axis.up, &dot.position);
	sum(&axis.right, &dot.position);
	drawline(axis.up, dot.position, green, vars);
	drawline(axis.right, dot.position, red, vars);
	
	//translate a relative point to world point
	draw_relative_point(dot, point);
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
