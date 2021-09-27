/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:45:22 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 18:30:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/engine.h"

void	init_eng(t_engine *eng)
{
	//inicia posição de origem
	init_obj(&eng->global, 0, WIDTH / 2, HEIGHT / 2, 0);
	eng->global.axis.up.y = -1;
	eng->on_scene = 0;
	//tela onde tudo sera renderizado
	create_img(&eng->screen, WIDTH, HEIGHT, &eng->vars);
	//axis angle will begin in 0
	vec_init(&eng->global.angle, 0, 0, 0);
	//scale begins in 1
	eng->global.axis.scale = 1;
	//obj that is being created
	eng->new_obj = 0;
	eng->is_creating = 0;
	eng->new_vertice.x = -1;
	eng->new_vertice.y = -1;
	eng->new_vertice.z = -1;

}