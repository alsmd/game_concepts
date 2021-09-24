/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 09:22:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"

float	radius = 30;
int	update(t_vars *vars)
{
	t_vec	mouse;
	t_vec	point;
	t_vec	circle_point;
	t_vec	dest_AB;
	int		x;
	int		y;
	float		ang = 0;
	int			color;
	
	mlx_clear_window(vars->mlx, vars->win);
	mlx_mouse_get_pos(vars->mlx, vars->win, &x, &y);
	vec_init(&circle_point, 0, 0);
	vec_init(&mouse, x, y);
	vec_init(&point, 100, 100);
	vec_magnitude(&point);
	vec_magnitude(&mouse);
	vec_init(&dest_AB, point.x - mouse.x, point.y - mouse.y);
	vec_magnitude(&dest_AB);
	if (dest_AB.magnitude < radius)
	{
		color = 0xff0000;
		mlx_pixel_put(vars->mlx, vars->win, (int) point.x, (int) point.y, 0xff0000);
	}
	else
	{
		color = 0xffff;
		mlx_pixel_put(vars->mlx, vars->win, (int) point.x, (int) point.y, 0X0000ff);
	}
	while (ang < 360)
	{
		circle_point.x = radius * cosf(ang);
		circle_point.y = radius * sinf(ang);
		vec_sum(&circle_point, &mouse);
		mlx_pixel_put(vars->mlx, vars->win, (int) circle_point.x, (int) circle_point.y, color);
		ang++;
	}
	return (1);
}

int	key(int keycode, t_vars *vars)
{
	if (keycode == 32)
		radius += 1;
	if (keycode == 65293)
		radius -= 1;
	return (1);
}

int main(void)
{
	t_vars	vars;
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
