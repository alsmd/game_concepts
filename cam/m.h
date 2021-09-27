/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2021/09/26 14:31:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_H
#define M_H
#include "../game_kit/game_kit.h"
#include <stdlib.h>
#include "mlx/mlx.h"
#include "X11/X.h"
#include <math.h>
#include <stdio.h>
#define WIDTH 1200
#define HEIGHT 500


typedef struct s_pro
{
	t_vars	vars;
	t_data	img;
	t_vec	*vel;
} t_pro;
void	create_img(t_data *img, int w, int h, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	load_img(t_data *img, char *path, t_vars *vars);
int		*to_array(int x, int y, int w, int h);
void	copy_img_to(t_data *dest, t_data *src, int info[4]);
void	copy_img_from(t_data *dest, t_data *src, int info[4]);
int		my_mlx_get_pixel(t_data *data, int x, int y);
void	clean_img(t_data *dest, int color, int width, int height);

#endif