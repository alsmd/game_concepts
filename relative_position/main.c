/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 19:14:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
#define red 0xff0000
#define green 0x00ff00
#define blue 0x0000ff

t_vars	vars;
float	angle;

void	put_pixel(t_vec point, int color)
{
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

int	update(t_vars *vars)
{
	t_obj	global;
	t_obj	another;
	t_obj	another_one;
	t_obj	dot;
	t_obj	point;
	t_axis	axis;
	t_vec	hold;
	
	//clean screen
	mlx_clear_window(vars->mlx, vars->win);
	//init global point and my obj that will be relative to this point
	init_obj(&global, 0, WIDTH / 2, HEIGHT / 2);
	init_obj(&dot, &global, 5, 5);
	//our dotte that will be relative to our object
	init_obj(&point, &dot, 20, 20);
	init_obj(&another, &point, 15, 5);
	init_obj(&another_one, &global, 10, 10);
	//rotate axis
	vec_rotate(&dot.axis.up, angle);
	vec_rotate(&dot.axis.right, angle);
	vec_rotate(&point.axis.up, 15);
	vec_rotate(&point.axis.right, 15);
	//scale axis and put in the right place to vizualization
	print_axis(dot, 100, drawline, vars);
	print_axis(point, 50, drawline, vars);
	print_axis(another, 30, drawline, vars);
	//translate a relative point to world point
	change_parent(&another_one, &another);
	hold = get_global_scope(another_one);
	put_pixel(hold, blue);
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
