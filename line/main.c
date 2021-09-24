/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 09:22:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"

int	update(t_vars *vars)
{
	t_vec	vec;
	t_vec	center;
	int		x;
	int		y;
	
	mlx_clear_window(vars->mlx, vars->win);
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	//mouse's position in relation of screen's top left
	//init all my vector's functions
	vec_init(&vec, x, y);
	//the point where our line will start
	center.x = WIDTH / 2;
	center.y = HEIGHT / 2;
	//vec will be relative to center
	vec_sub(&vec, &center);
	//take magnitude of currently x and y, it will be stored in vec->magnitude // it will be relative to center
	vec_magnitude(&vec);
	//normalize the length (magnitude) to 1
	vec_normalize(&vec);
	//scale for the size that i want my line to be
	vec_scale(&vec, 100);
	//make this new point be relative to the screen again
	vec_sum(&vec, &center);
	//draw the line
	drawline(center.x, center.y, vec.x, vec.y, vars);
	/* printf("x: %f\n", vec.x);
	printf("y: %f\n", vec.y);
	printf("magnitude: %f\n", vec.magnitude);
	fflush(stdin); */
}

int main(void)
{
	t_vars	vars;
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	mlx_loop_hook(vars.mlx, update, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
