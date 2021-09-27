/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:47:15 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 19:18:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine.h"

int	update(t_engine *eng)
{
	clean_img(&eng->screen, 0, WIDTH, HEIGHT);
	print_axis(eng->global, 100, eng);
	render_objs(eng);
	mlx_put_image_to_window(eng->vars.mlx, eng->vars.win, eng->screen.img, 0, 0);
	return (1);
}

int	mouse_event(int action, int x, int y, t_engine *eng)
{
	t_vec	vec;
	t_vec	tmp;

	if (action == LEFT_CLICK)
	{
		/* if (eng->new_obj != 0)
		{
			vec_init(&vec, x, y, 0);
			put_pixel(vec, 0xfa0f00, eng);
			add_vertice(eng, x, y);
		} */
	}
	if (action == 4)
	{
		eng->global.axis.scale += 0.2;
	}
	if (action == 5)
	{
		eng->global.axis.scale -= 0.2;
	}
	printf("%d\n", action);

	return (1);
}

int	key_event(int keycode, t_engine *eng)
{
	static int	cord;

	if (eng->is_creating && (keycode >= 48 && keycode <= 57))
		cord = cord * 10 + (keycode - 48);
	if (keycode == ESQ_KEY)
		add_obj(eng);
	if (eng->is_creating && keycode == ENTER_KEY && has_three_ver(eng))
		save_obj(eng);
	else if (eng->is_creating && keycode == ENTER_KEY)
	{
		cord_to_vertice(cord, eng);
		cord = 0;
	}
	if (keycode == A_KEY)
		rotatey_axis(&eng->global.axis, -1);
	if (keycode == D_KEY)
		rotatey_axis(&eng->global.axis, 1);
	if (keycode == W_KEY)
		rotatex_axis(&eng->global.axis, 1);
	if (keycode == S_KEY)
		rotatex_axis(&eng->global.axis, -1);
	if (keycode == UP_KEY)
		eng->global.position.y += 10;
	if (keycode == DOWN_KEY)
		eng->global.position.y -= 10;
	if (keycode == LEFT_KEY)
		eng->global.position.x += 10;
	if (keycode == RIGHT_KEY)
		eng->global.position.x -= 10;
	printf("cord: %d\n", cord);
	fflush(stdout);
	return(1);
}