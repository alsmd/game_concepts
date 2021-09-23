/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/23 13:03:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"
t_vars	vars;

void	put_pixel(t_vec point, int color)
{
	mlx_pixel_put(vars.mlx, vars.win, point.x, point.y, color);
}

int	update(t_vars *vars)
{
	t_vec	player;
	t_vec	enemy;
	float	dot;

	vec_init(&player, 250, 15);
	vec_init(&enemy, 130, 130);
	put_pixel(player, 0x00ff00);
	put_pixel(enemy, 0xff0000);
	magnitude(&player);
	magnitude(&enemy);
	normalize(&player);
	dot = (player.x * enemy.x) + (player.y * enemy.y);
	scale(&player, dot);
	put_pixel(player, 0x0000ff);
	printf("%f\n", dot);
	return (1);
}


int main(void)
{
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	mlx_loop_hook(vars.mlx, update, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
