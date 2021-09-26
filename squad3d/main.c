/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 18:13:41 by user42           ###   ########.fr       */
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
float	scale = 1;
float	desloc = 0;
float	angle;
t_obj	global;
t_square	square = {
	.point[0] = {
		.x = -10,
		.y = -10,
		.z = 100
	},
	.point[1] = {
		.x = -100,
		.y = -10,
		.z = 100
	},
	.point[2] = {
		.x = -100,
		.y = -100,
		.z = 100
	},
	.point[3] = {
		.x = -10,
		.y = -100,
		.z = 100
	},
	//atraz
	.point[4] = {
		.x = -10,
		.y = -10,
		.z = -100
	},
	.point[5] = {
		.x = -100,
		.y = -10,
		.z = -100
	},
	.point[6] = {
		.x = -100,
		.y = -100,
		.z = -100
	},
	.point[7] = {
		.x = -10,
		.y = -100,
		.z = -100
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

void	drawline1(t_vec vec1, t_vec vec2, int color, t_vars *vars)
{
	t_axis	axis;

	//vec1
	axis = global.axis;
	vec_scale(&axis.center, vec1.z);
	vec_scale(&axis.up, vec1.y);
	vec_scale(&axis.right, vec1.x);
	vec_sum(&vec1, &axis.center);
	vec_sum(&vec1, &axis.up);
	vec_sum(&vec1, &axis.right);
	vec_sum(&vec1, &global.position);
	//vec2
	axis = global.axis;
	vec_scale(&axis.center, vec2.z);
	vec_scale(&axis.up, vec2.y);
	vec_scale(&axis.right, vec2.x);
	vec_sum(&vec2, &axis.center);
	vec_sum(&vec2, &axis.up);
	vec_sum(&vec2, &axis.right);
	vec_sum(&vec2, &global.position);
	
	vec_scale(&vec1, scale);
	vec_scale(&vec2, scale);
	vec1.x += desloc;
	vec2.x += desloc;
	drawline(vec1, vec2, color, vars);
}

void	print_square()
{
	int	index;

	index = 0;
	//front face
	drawline1(square.point[0], square.point[1], 0x0000ff, &vars);
	drawline1(square.point[2], square.point[3], 0x0000ff, &vars);
	drawline1(square.point[0], square.point[3], 0x0000ff, &vars);
	drawline1(square.point[1], square.point[2], 0x0000ff, &vars);
	//back face
	drawline1(square.point[0 + 4], square.point[1 + 4], 0x00ff00, &vars);
	drawline1(square.point[2 + 4], square.point[3 + 4], 0x00ff00, &vars);
	drawline1(square.point[0 + 4], square.point[3 + 4], 0x00ff00, &vars);
	drawline1(square.point[1 + 4], square.point[2 + 4], 0x00ff00, &vars);
	//up and down
	drawline1(square.point[0 + 4], square.point[0], 0xff0000, &vars);
	drawline1(square.point[1 + 4], square.point[1], 0xff0000, &vars);
	drawline1(square.point[2 + 4], square.point[2], 0xff0000, &vars);
	drawline1(square.point[3 + 4], square.point[3], 0xff0000, &vars);
	
	/* while (index < 8)
	{
		put_pixel(square.point[index], 0xff0000);
		index++;
	} */
}

int	update(t_vars *vars)
{
	t_vec	point;

	mlx_clear_window(vars->mlx, vars->win);
	init_obj(&global, 0, WIDTH / 2, HEIGHT / 2, 0);
	//x
	vec_rotatex(&global.axis.center, 10);
	vec_rotatex(&global.axis.up, 10);
	vec_rotatex(&global.axis.right, 10);
	//z
	vec_rotatez(&global.axis.center, 10);
	vec_rotatez(&global.axis.up, 10);
	vec_rotatez(&global.axis.right, 10);
	//y
	vec_rotatey(&global.axis.center, angle);
	vec_rotatey(&global.axis.up, angle);
	vec_rotatey(&global.axis.right, angle);
	
	//print_axis(global, 200, drawline, vars);
	angle += 0.06;
	print_square();
	return (1);
}

int	key(int keycode, void *v)
{
	const int	left = 65361;
	const int	right = 65363;
	const int	up = 65362;
	const int	down = 65364;
	const float	speed = 10;

	if (keycode == left)
		desloc += speed;
	if (keycode == right)
		desloc -= speed;
	if (keycode == up)
		scale += 0.1;
	if (keycode == down)
		scale -= 0.1;
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
