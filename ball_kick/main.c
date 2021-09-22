/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/22 15:31:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"

void	img_to_window(t_vars *vars, t_data *img, t_vec *position)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, (int) position->x, (int) position->y);
}

void	on_screen(t_pro *program)
{
	static int	count;
	int			x;
	int			y;

	x = program->position->x;
	y = program->position->y;
	program->vel->sum(program->vel, program->acel);
	if ((x + (program->img.w / 2) > WIDTH) || (x < (0 - program->img.w / 2)))
		program->vel->x *= -1;
	if ((y + ( program->img.h / 2) > HEIGHT) || (y <  (0 - ( program->img.h / 2))))
		program->vel->y *= -1;
	count++;
	if (count > 50)
	{
		program->acel->scale(program->acel, -1);
		count = 0;
	}
}

int	update(t_pro *program)
{
	program->position->sum(program->position, program->vel);
	img_to_window(&program->vars, &program->img, program->position);
	on_screen(program);
	return (1);
}

int main(void)
{
	t_pro	program;

	program.img.w = 30;
	program.img.h = 30;
	program.position = new_vec(0, 0);
	program.vel = new_vec(0, 0);
	program.acel = new_vec(.001f, 0.01f);
    program.vars.mlx = mlx_init();
    program.vars.win = mlx_new_window(program.vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	load_img(&program.img, "ball.xpm", &program.vars);
	mlx_loop_hook(program.vars.mlx, update, &program.vars);
    mlx_loop(program.vars.mlx);
    return (0);
}
