#include "mlx/mlx.h"
#include "X11/X.h"
#include <math.h>
#include <stdio.h>

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;

typedef struct s_vec
{
	float x,y,z;
} t_vec;

typedef struct s_tri
{
	t_vec	v[3];
}	t_tri;

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

void	create_img(t_data *img, int w, int h, t_vars *vars)
{
	img->img = mlx_new_image(vars->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endin);
}

void drawline(int x0, int y0, int x1, int y1, t_data *img);
#define HEIGHT 500
#define WIDTH 500
t_vars  vars;

void	mult_vec(t_vec in, t_vec *out, float m[4][4], int a)
{
	out->x = in.x * m[0][0] + in.y * m[1][0] + in.z * m[2][0] + m[3][0];
	out->y = in.x * m[0][1] + in.y * m[1][1] + in.z * m[2][1] + m[3][1];
	out->z = in.x * m[0][2] + in.y * m[1][2] + in.z * m[2][2] + m[3][2];

	float w = in.x * m[0][3] + in.y * m[1][3] + in.z * m[2][3] + m[3][3];

	if (w != 0.0f)
	{
		out->x /= w;
		out->y /= w;
		out->z /= w;
	}
	//scale into view
	if (a)
	{
		out->x += 1;
		out->y += 1;
		out->x *= 0.5 * (float)(WIDTH);
		out->y *= 0.5 * (float)(HEIGHT);
	}
		/* printf("x: %f\n", out->x);
		printf("y: %f\n", out->y);
		printf("z: %f\n", out->z); */
}
#include <time.h>
clock_t		clock_var = 0;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		bytes;

	bytes = (data->bits_per_pixel / 8);
	dest = data->addr + (y * data->line_length + x * bytes);
	*(unsigned int *)dest = color;
}
#include <stdlib.h>


int	update(void *null)
{
	t_tri	tri = {
		.v[0] = {
			.x = 0,
			.y = 0,
			.z = 0
		},
		.v[1] = {
			.x = 1,
			.y = 0,
			.z = 1
		},
		.v[2] = {
			.x = 1,
			.y = 1,
			.z = 1
		}
	};
	float	Near = 0.1f;
	float	Far = 1000.0f;
	float	Fov = 90.0f;
	float	AspectRatio = (float)HEIGHT / (float)WIDTH;
	float	FovRad = 1.0f / tan(Fov * 0.5f / 180.0f * 3.14159f);
	float	proj[4][4] = {
		{AspectRatio * FovRad, 0, 0, 0},
		{0, FovRad, 0, 0},
		{0, 0, Far / (Far - Near), 1},
		{0, 0, (-(Far) * Near) / (Far - Near), 0}
	};
	float	rotZ[4][4], rotX[4][4];
	static float	theta;
	theta += 1.0f * ((float)(clock() - clock_var) / CLOCKS_PER_SEC);
	clock_var = clock();
	//Rotation z
rotZ[0][0] = cosf(theta);
		rotZ[0][1] = sinf(theta);
		rotZ[1][0] = -sinf(theta);
		rotZ[1][1] = cosf(theta);
		rotZ[2][2] = 1;
		rotZ[3][3] = 1;
	rotZ[3][3] = 1;
	//Rotation x
		rotX[0][0] = 1;
		rotX[1][1] = cosf(theta * 0.5f);
		rotX[1][2] = sinf(theta * 0.5f);
		rotX[2][1] = -sinf(theta * 0.5f);
		rotX[2][2] = cosf(theta * 0.5f);
		rotX[3][3] = 1;
	t_tri	tri_projected, tri_translated, tri_rotatedZ, tri_rotatedX;
	int		index = 0;
	while (index < 3)
	{
		mult_vec(tri.v[index], &tri_rotatedZ.v[index], rotZ, 0);
		index++;
	}
	index = 0;

	while (index < 3)
	{
		mult_vec(tri_rotatedZ.v[index], &tri_rotatedX.v[index], rotX, 0);
		index++;
	}
	index = 0;

	tri_translated = tri_rotatedX;
	tri_translated.v[0].z = tri_rotatedX.v[0].z + 3.0f;
	tri_translated.v[1].z = tri_rotatedX.v[1].z + 3.0f;
	tri_translated.v[2].z = tri_rotatedX.v[2].z + 3.0f;
	while (index < 3)
	{
		mult_vec(tri_translated.v[index], &tri_projected.v[index], proj, 1);
		index++;
	}
	t_data	img;

	create_img(&img, WIDTH, HEIGHT, &vars);
	mlx_clear_window(vars.mlx, vars.win);
	drawline(tri_projected.v[0].x, tri_projected.v[0].y, tri_projected.v[1].x, tri_projected.v[1].y, &img);
	drawline(tri_projected.v[1].x, tri_projected.v[1].y, tri_projected.v[2].x, tri_projected.v[2].y, &img);
	drawline(tri_projected.v[2].x, tri_projected.v[2].y, tri_projected.v[0].x, tri_projected.v[0].y, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0 ,0);
	free(img.img);
}

int main(void)
{
	/* float	proj[4][4];
	proj[0][0] = AspectRatio * FovRad;
	proj[1][1] = FovRad;
	proj[2][2] = Far / (Far - Near);
	proj[3][2] = (-Far * Near) / (Far - Near);
	proj[2][3] = 1.0f;
	proj[3][3] = 0.0f; */
	clock_var = clock();
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello Dotes");
	mlx_loop_hook(vars.mlx, update, &vars);
    mlx_loop(vars.mlx);
    return (0);
}


int	take_step(float dx, float dy)
{
	if (dx < 0)
		dx *= -1;
	if (dy < 0)
		dy *= -1;
	return (dx > dy ? dx : dy);
}

void drawline(int x0, int y0, int x1, int y1, t_data *img)
{
    double	dx, dy, x, y;
    int		steps;

    dx=x1-x0;
    dy=y1-y0;
    
	x = x0;
	y = y0;
	steps = take_step(dx, dy);
	dx = (double) (dx / steps);
	dy = (double) (dy / steps);
	while (steps--)
	{
		if ((x > 0 && y > 0) && (x <= WIDTH && y <= HEIGHT))
		{
			//printf("x: %f\n",  x);
			//printf("y: %f\n",  y);
			my_mlx_pixel_put(img, x, y, 0xfffff);
			//mlx_pixel_put(vars.mlx, vars.win, x, y, 0xfffff);
		}
		x += dx;
		y += dy;
	}
}
