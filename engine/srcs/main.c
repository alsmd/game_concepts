/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:29:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 17:55:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/engine.h"

t_obj	*obj = 0;

int main(void)
{
	t_engine	eng;
	
	eng.vars.mlx = mlx_init();
	eng.vars.win = mlx_new_window(eng.vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	init_eng(&eng);
	mlx_hook(eng.vars.win, KeyPress, KeyPressMask, key_event, &eng);
	mlx_loop_hook(eng.vars.mlx, update, &eng);
	mlx_mouse_hook(eng.vars.win, mouse_event, &eng);
	mlx_loop(eng.vars.mlx);
    return (0);
}
