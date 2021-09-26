/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 09:43:44 by user42           ###   ########.fr       */
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
t_vec	desloc;
t_vec	angle;
t_obj	cam;

void	put_pixel(t_vec point, int color)
{
	t_axis	axis;

	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

void	change_value(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	rotate_axis(t_axis *axis)
{
	vec_rotatey(&axis->up, angle.y);
	vec_rotatey(&axis->center, angle.y);
	vec_rotatey(&axis->right, angle.y);

	vec_rotatex(&axis->up, angle.x);
	vec_rotatex(&axis->center, angle.x);
	vec_rotatex(&axis->right, angle.x);

	vec_rotatez(&axis->up, angle.z);
	vec_rotatez(&axis->center, angle.z);
	vec_rotatez(&axis->right, angle.z);
}

void	draw_tri(t_obj tri[3])
{
	int	index;

	index = 0;
	while (index < 3)
	{
		tri[index].position = get_global_scope(tri[index]);
		index++;
	}
	drawline(tri[0].position, tri[1].position, 0x0000ff, &vars);
	drawline(tri[1].position, tri[2].position, 0x0000ff, &vars);
	drawline(tri[2].position, tri[0].position, 0x0000ff, &vars);
}

void	draw_square()
{
	t_obj	tris[10][3];

	//front
	init_obj(&tris[0][0], &cam, 0, 0, 0);
	init_obj(&tris[0][0], &cam, 0, 100, 0);
	init_obj(&tris[0][0], &cam, 100, 0, 0);
	draw_tri(tris[0]);
	
	init_obj(&tris[0][0], &cam, 0, 0, 0);
	init_obj(&tris[0][0], &cam, 0, 0, 0);
	init_obj(&tris[0][0], &cam, 0, 0, 0);
}

int	update(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	init_obj(&cam, 0, 0, 0, 0);
	cam.position.y += HEIGHT + desloc.y;
	cam.position.x += desloc.x;
	cam.axis.up.y = -1;
	rotate_axis(&cam.axis);
	print_axis(cam, 300, drawline, vars);
	//draw point
	draw_square();
	return (1);
}

int	key(int keycode, void *v)
{
	const int	left = 65361;
	const int	right = 65363;
	const int	up = 65362;
	const int	down = 65364;
	const int	a = 97;
	const int	w = 119;
	const int	s = 115;
	const int	d = 100;
	const float	speed = 10;

	if (keycode == left)
		desloc.x -= speed;
	if (keycode == right)
		desloc.x += speed;
	if (keycode == up)
		desloc.y -= speed;
	if (keycode == down)
		desloc.y += speed;
	if (keycode == a)
		angle.y += 1;
	if (keycode == d)
		angle.y -= 1;
	if (keycode == w)
		angle.x += 1;
	if (keycode == s)
		angle.x -= 1;
	printf("%d\n", keycode);
	fflush(stdout);
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
