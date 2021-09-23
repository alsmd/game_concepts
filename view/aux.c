/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 08:30:16 by user42            #+#    #+#             */
/*   Updated: 2021/09/22 14:09:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m.h"

void	create_img(t_data *img, int w, int h, t_vars *vars)
{
	img->img = mlx_new_image(vars->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endin);
}

int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

void drawline(int x0, int y0, int x1, int y1, t_vars *vars)
{
	//t_data	img;
    double	dx, dy, x, y;
    int		steps;

    dx=x1-x0;
    dy=y1-y0;
    
	x = x0;
	y = y0;
	//create_img(&img, WIDTH, HEIGHT, vars);
	steps = take_step(dx, dy);
	dx = (double) (dx / steps);
	dy = (double) (dy / steps);
	while (steps--)
	{
		if ((x > 0 && y > 0) && (x <= WIDTH && y <= HEIGHT))
		{
			//my_mlx_pixel_put(&img, x, y, 0xfffff);
			mlx_pixel_put(vars->mlx, vars->win, x, y, 0xfffff);
		}
		x += dx;
		y += dy;
	}
	//mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	//free(img.img);
}

void	load_img(t_data *img, char *path, t_vars *vars)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endin);
}