/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 18:42:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_H
#define M_H
#include "../../game_kit/game_kit.h"
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "X11/X.h"
#include <math.h>
#include <stdio.h>
#define WIDTH 1200
#define HEIGHT 500

void	create_img(t_data *img, int w, int h, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	load_img(t_data *img, char *path, t_vars *vars);
int		*to_array(int x, int y, int w, int h);
void	copy_img_to(t_data *dest, t_data *src, int info[4]);
void	copy_img_from(t_data *dest, t_data *src, int info[4]);
int		my_mlx_get_pixel(t_data *data, int x, int y);
void	clean_img(t_data *dest, int color, int width, int height);

void	put_pixel(t_vec point, int color, t_engine *eng);
//init
void	init_eng(t_engine *eng);
//events
int	update(t_engine *eng);
int	mouse_event(int action, int x, int y, t_engine *eng);
int	key_event(int keycode, t_engine *eng);
//obj
void	add_obj(t_engine *eng);
void	save_obj(t_engine *eng);
void	render_objs(t_engine *eng);

//vertices
void	add_vertice(t_engine *eng);
void	print_vertices(t_vec *vertice, t_engine *eng);
void	proj_vec(t_vec *vec, t_engine *eng);
void	cord_to_vertice(int cord, t_engine *eng);
int		has_three_ver(t_engine *eng);

#endif