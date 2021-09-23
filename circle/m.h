/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:25:49 by user42            #+#    #+#             */
/*   Updated: 2021/09/23 11:19:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_H
#define M_H
#include "../vec_lib/vec.h"
#include <stdlib.h>
#include "mlx/mlx.h"
#include "X11/X.h"
#include <math.h>
#include <stdio.h>
#define WIDTH 255
#define HEIGHT 255


typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endin;
	int		w;
	int		h;
}	t_data;

typedef struct s_pro
{
	t_vars	vars;
	t_data	img;
	t_vec	*vel;
} t_pro;
void	drawline(int x0, int y0, int x1, int y1, t_vars *vars);
void	create_img(t_data *img, int w, int h, t_vars *vars);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	load_img(t_data *img, char *path, t_vars *vars);
int		*to_array(int x, int y, int w, int h);
void	copy_img_to(t_data *dest, t_data *src, int info[4]);
void	copy_img_from(t_data *dest, t_data *src, int info[4]);
int		my_mlx_get_pixel(t_data *data, int x, int y);
t_vec	*new_vec(float x, float y);

#endif