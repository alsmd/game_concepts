/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/23 19:07:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
t_vars	vars;

void	put_pixel(t_vec point, int color)
{
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

void	rotate(t_vec *vec, t_vec *vec_proj, float	angle)
{
	float	rad;

	rad = angle * M_PI / 100;
	
	vec_proj->x = vec->x * cos(rad) - vec->y * sin(rad);
	vec_proj->y = vec->y * cos(rad) + vec->x * sin(rad);
}

typedef struct s_tri
{
	t_vec point[3];
} t_tri;

float	angle;
int	update(t_vars *vars)
{
	t_tri tri;
	t_tri tri_projected;
	t_vec	center;

	mlx_clear_window(vars->mlx, vars->win);
	vec_init(&tri.point[0], 0, 0);
	vec_init(&tri.point[1], 50, 0);
	vec_init(&tri.point[2], 0, 50);
	vec_init(&center, WIDTH / 2, HEIGHT / 2);
	//rotate
	rotate(&tri.point[0], &tri_projected.point[0], angle);
	rotate(&tri.point[1], &tri_projected.point[1], angle);
	rotate(&tri.point[2], &tri_projected.point[2], angle);

	
	sum(&tri_projected.point[0], &center);
	sum(&tri_projected.point[1], &center);
	sum(&tri_projected.point[2], &center);
	put_pixel(center, 0x0000ff);
	drawline(tri_projected.point[0], tri_projected.point[1], 0xff0000, vars);
	drawline(tri_projected.point[1], tri_projected.point[2], 0xff0000, vars);
	drawline(tri_projected.point[2], tri_projected.point[0], 0xff0000, vars);
	return (1);
}

int	key(int keycode, void *v)
{
	const int	up = 65362;
	const int	down = 65364;
	const float	speed = 2;

	if (keycode == up)
		angle -= speed;
	if (keycode == down)
		angle += speed;
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
