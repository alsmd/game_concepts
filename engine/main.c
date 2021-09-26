/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 12:35:59 by user42           ###   ########.fr       */
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
t_data	img;
t_obj	tris[12][3];

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

static int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

void fill(t_vec vec1, t_vec vec2, t_vec vec3,  int color, t_vars *vars)
{
	t_vec	d_vec1;
    int		steps;

	d_vec1.x = vec2.x - vec1.x;
	d_vec1.y = vec2.y - vec1.y;
	
	steps = take_step(d_vec1.x, d_vec1.y);
	d_vec1.x /= steps;
	d_vec1.y /= steps;

	while (steps--)
	{
		drawline(vec1, vec3, color, vars, &img);
		vec_sum(&vec1, &d_vec1);
	}
}
void	draw_tri(t_obj tri[3])
{
	t_vec	projected[3];
	int	index;

	index = 0;
	while (index < 3)
	{
		projected[index] = get_global_scope(tri[index]);
		vec_scale(&projected[index], scale);
		index++;
	}
	fill(projected[0], projected[1], projected[2], 0x009fe1, &vars);

}

void	draw_square()
{

	//front
	draw_tri(tris[0]);
	
	draw_tri(tris[1]);
	//left
	draw_tri(tris[2]);
	
	draw_tri(tris[3]);

	//right
	draw_tri(tris[4]);
	
	draw_tri(tris[5]);
	//back
	draw_tri(tris[6]);
	
	draw_tri(tris[7]);

	//top
	draw_tri(tris[8]);
	
	draw_tri(tris[9]);

	//bottom

	draw_tri(tris[10]);
	
	draw_tri(tris[11]);

}

void	make_tri()
{
	//front
	init_obj(&tris[0][0], &cam, 0, 0, 0);
	init_obj(&tris[0][1], &cam, 0, 100, 0);
	init_obj(&tris[0][2], &cam, 100, 0, 0);
	
	init_obj(&tris[1][0], &cam, 0, 100, 0);
	init_obj(&tris[1][1], &cam, 100, 100, 0);
	init_obj(&tris[1][2], &cam, 100, 0, 0);
	//left
	init_obj(&tris[2][0], &cam, 0, 0, 0);
	init_obj(&tris[2][1], &cam, 0, 100, 0);
	init_obj(&tris[2][2], &cam, 0, 0, 100);
	
	init_obj(&tris[3][0], &cam, 0, 100, 0);
	init_obj(&tris[3][1], &cam, 0, 100, 100);
	init_obj(&tris[3][2], &cam, 0, 0, 100);

	//right
	init_obj(&tris[4][0], &cam, 100, 0, 0);
	init_obj(&tris[4][1], &cam, 100, 100, 0);
	init_obj(&tris[4][2], &cam, 100, 0, 100);
	
	init_obj(&tris[5][0], &cam, 100, 100, 0);
	init_obj(&tris[5][1], &cam, 100, 100, 100);
	init_obj(&tris[5][2], &cam, 100, 0, 100);


	//back
	init_obj(&tris[6][0], &cam, 0, 0, 100);
	init_obj(&tris[6][1], &cam, 0, 100, 100);
	init_obj(&tris[6][2], &cam, 100, 0, 100);
	
	init_obj(&tris[7][0], &cam, 0, 100, 100);
	init_obj(&tris[7][1], &cam, 100, 100, 100);
	init_obj(&tris[7][2], &cam, 100, 0, 100);

	//top
	init_obj(&tris[8][0], &cam, 0, 100, 0);
	init_obj(&tris[8][1], &cam, 0, 100, 100);
	init_obj(&tris[8][2], &cam, 100, 100, 0);
	
	init_obj(&tris[9][0], &cam, 0, 100, 100);
	init_obj(&tris[9][1], &cam, 100, 100, 100);
	init_obj(&tris[9][2], &cam, 100, 100, 0);

	//bottom
	init_obj(&tris[10][0], &cam, 0, 0, 0);
	init_obj(&tris[10][1], &cam, 0, 0, 100);
	init_obj(&tris[10][2], &cam, 100, 0, 0);
	
	init_obj(&tris[11][0], &cam, 0, 0, 100);
	init_obj(&tris[11][1], &cam, 100, 0, 100);
	init_obj(&tris[11][2], &cam, 100, 0, 0);
}

void	draw_edges()
{
	t_vec	projected[2];
	//front left
	projected[0] = get_global_scope(tris[0][0]);
	projected[1] = get_global_scope(tris[0][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);

	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//front right
	projected[0] = get_global_scope(tris[1][1]);
	projected[1] = get_global_scope(tris[1][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//front top
	projected[0] = get_global_scope(tris[0][1]);
	projected[1] = get_global_scope(tris[1][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//front bottom
	projected[0] = get_global_scope(tris[0][0]);
	projected[1] = get_global_scope(tris[1][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);


	//back left
	projected[0] = get_global_scope(tris[6][0]);
	projected[1] = get_global_scope(tris[6][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//back right
	projected[0] = get_global_scope(tris[7][1]);
	projected[1] = get_global_scope(tris[7][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//back top
	projected[0] = get_global_scope(tris[6][1]);
	projected[1] = get_global_scope(tris[7][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//back bottom
	projected[0] = get_global_scope(tris[6][0]);
	projected[1] = get_global_scope(tris[7][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);

	//top left
	projected[0] = get_global_scope(tris[0][1]);
	projected[1] = get_global_scope(tris[6][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//top right
	projected[0] = get_global_scope(tris[1][1]);
	projected[1] = get_global_scope(tris[7][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//top top
	projected[0] = get_global_scope(tris[6][1]);
	projected[1] = get_global_scope(tris[7][1]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//top bottom
	projected[0] = get_global_scope(tris[6][0]);
	projected[1] = get_global_scope(tris[7][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);


	//bottom left
	projected[0] = get_global_scope(tris[0][0]);
	projected[1] = get_global_scope(tris[6][0]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//bottom right
	projected[0] = get_global_scope(tris[0][2]);
	projected[1] = get_global_scope(tris[6][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//bottom top
	projected[0] = get_global_scope(tris[6][0]);
	projected[1] = get_global_scope(tris[7][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
	//bottom bottom
	projected[0] = get_global_scope(tris[6][0]);
	projected[1] = get_global_scope(tris[7][2]);
	vec_scale(&projected[0], scale);
	vec_scale(&projected[1], scale);
	drawline(projected[0], projected[1], 0xfa0040, &vars, &img);
}

int	update(t_vars *vars)
{
	init_obj(&cam, 0, 0, 0, 0);
	cam.position.y += HEIGHT + desloc.y;
	cam.position.x += desloc.x;
	cam.axis.up.y = -1;
	rotate_axis(&cam.axis);
	clean_img(&img, 0x76ff76, WIDTH, HEIGHT);
	//print_axis(cam, 300, drawline, vars);
	//draw point
	draw_square();
	draw_edges();
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);

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
		angle.y -= 1;
	if (keycode == d)
		angle.y += 1;
	if (keycode == w)
		angle.x += 1;
	if (keycode == s)
		angle.x -= 1;
	//printf("%d\n", keycode);
	//fflush(stdout);
}

int	scroll(int action, t_vars *vars)
{
	if (action == 4)
		scale += .2;
	if (action == 5)
		scale -= .2;
	printf("%d\n", action);
	fflush(stdout);
}

int main(void)
{
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	create_img(&img, WIDTH, HEIGHT, &vars);
	make_tri();

	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key, 0);
	mlx_mouse_hook(vars.win, scroll, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
