/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 15:57:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
#define red 0xff0000
#define green 0x00ff00
#define blue 0x0000ff
typedef	struct s_square
{
	t_vec	point[10];
}	t_square;

t_vars	vars;
float	anglex = 0;
float	angley = 0;
float	anglez = 0;
t_obj	global;
t_square	square = {
	.point[0] = {
		.x = -10,
		.y = -10,
		.z = -0
	},
	.point[1] = {
		.x = -100,
		.y = -10,
		.z = -0
	},
	.point[2] = {
		.x = -100,
		.y = -100,
		.z = -0
	},
	.point[3] = {
		.x = -10,
		.y = -100,
		.z = -0
	},
	//atraz
	.point[4] = {
		.x = -10,
		.y = -10,
		.z = -50
	},
	.point[5] = {
		.x = -100,
		.y = -10,
		.z = -50
	},
	.point[6] = {
		.x = -100,
		.y = -100,
		.z = -50
	},
	.point[7] = {
		.x = -10,
		.y = -100,
		.z = -50
	}
};
void	put_pixel(t_vec point, int color)
{
	t_axis	axis;

	axis = global.axis;
	vec_scale(&axis.center, point.z);
	vec_sum(&point, &axis.center);
	vec_sum(&point, &global.position);
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

int	update(t_vars *vars)
{
	t_obj	global;
	t_obj	point;

	mlx_clear_window(vars->mlx, vars->win);
	init_obj(&global, 0, WIDTH / 2, HEIGHT / 2, 0);
	init_obj(&point, &global, 10, 10, 100);
	//x
	vec_rotatex(&global.axis.center, anglex);
	vec_rotatex(&global.axis.up, anglex);
	vec_rotatex(&global.axis.right, anglex);

	//y
	vec_rotatey(&global.axis.center, angley);
	vec_rotatey(&global.axis.up, angley);
	vec_rotatey(&global.axis.right, angley);
	//z
	vec_rotatez(&global.axis.center, anglez);
	vec_rotatez(&global.axis.up, anglez);
	vec_rotatez(&global.axis.right, anglez);
	
	printf("x %f\n", global.axis.right.x);
	printf("y %f\n", global.axis.right.y);
	printf("z %f\n", global.axis.right.z);
	print_axis(global, 50, drawline, vars);

	point.position = get_global_scope(point);
	put_pixel(point.position, 0xffff);
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
		anglez -= speed;
	if (keycode == up)
		angley += speed;
	if (keycode == right)
		anglex += speed;
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
