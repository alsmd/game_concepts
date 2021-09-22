#include "mlx/mlx.h"
#include "X11/X.h"
#include <math.h>
#include <stdio.h>

typedef struct position
{
    int  x;
    int  y;
}   position;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}   t_vars;
void    draw(t_vars *vars, double x, double y, int color);

/* void drawline(int x0, int y0, int x1, int y1, t_vars *vars)
{
    int dx, dy, p, x, y;
 
    dx=x1-x0;
    dy=y1-y0;
    
    x=x0;
    y=y0;
    p=dy-dx;
    while(x<x1)
    {
        if(p>=0)
        {
            mlx_pixel_put(vars->mlx, vars->win, x,y, 0x0000FF);
            y=y+1;
            p=p+dy-dx;
        }
        else
        {
            mlx_pixel_put(vars->mlx, vars->win, x,y, 0x0000FF);
            p=p+dy;
        }
        x=x+1;
    }
} */


int update(t_vars *vars)
{
    position    p;
    double      d;
    int         x;
    int         y;
    int         scale;

    scale = 1;
    mlx_mouse_get_pos(vars->mlx, vars->win, &p.x, &p.y);
    d = sqrt((p.x * p.x) + (p.y * p.y));
    //printf("%f\n", d);
    x =  (int) ((p.x / d) * 100);
    y = (int) ((p.y / d) * 100);
    mlx_clear_window(vars->mlx, vars->win);

    while (scale < 15)
    {
        mlx_pixel_put(vars->mlx, vars->win, (int) x * scale, (int) y * scale, 0XFFFF);
        scale++;
    }

    //draw(vars, (double) x, (double) y, 0XFFFF);
}

int x(int pt[3])
{
	return (pt[0] / pt[2]) * 100;
}

int y(int pt[3])
{
	return (pt[1] / pt[2]) * 100;
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
		mlx_pixel_put(vars->mlx, vars->win, x, y, 0xfffff);
		x += dx;
		y += dy;
	}
}

void	multiplication(int	p[3], float ang)
{
	int	fov = 25;
	int		mult[3][3] = {
		{1,0,0},
		{0,1,0},
		{0,0,0}
	};
	double	r_z[3][3] = {
		{cos(ang), -sin(ang), 0},
		{sin(ang), cos(ang), 0},
		{0, 0, 1}
	};
	p[0] = (r_z[0][0] * p[0] * r_z[0][1]) * p[0];
	p[1] = (r_z[1][0] * p[1] * r_z[1][1]) * p[0];
}
int	init[2] = {500 / 2, 500 / 2};

int	ta(t_vars *vars)
{
	int		cub[8][3] = {
		//frente
		{0,0,0},{1,0,0},{1,1,0},{0,1,0},
		//traz
		{0,0,1},{1,0,1},{1,1,1},{0,1,1}
	};
	int		index = 0;
	int		scale = 100;
	static float	ang = 0;

	mlx_clear_window(vars->mlx, vars->win);
	while (index < 8)
	{
		multiplication(cub[index], 1);
		mlx_pixel_put(vars->mlx, vars->win, (cub[index][0] * scale), (cub[index][1] * scale), 0xfffff);
		index++;
	}
	ang += .1;
	printf("%f", ang);
}

int main(void)
{
    t_vars  vars;
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello Dotes");
	
	ta(&vars);
    mlx_loop_hook(vars.mlx, ta, &vars);
    //drawline(x(p1), y(p1), x(p2), y(p2), &vars);
    mlx_loop(vars.mlx);
    return (0);
}


void    draw(t_vars *vars, double x, double y, int color)
{
    double  ix;
    double  iy;
    double  coeficient;

    ix = 0;
    iy = 0;
    coeficient = (x - iy) / (y - ix);
    while (x > 0 || y > 0)
    {
        y -= coeficient;
        mlx_pixel_put(vars->mlx, vars->win, (int) x, (int) y, color);
        if (x > 0)
            x -= 1;
    }
}

/* void    draw_graph(t_vars *vars, int width, int height)
{
    position    p1;
    position    p2;
    int         x;

    x = 0;
    while (x < height)
    {
        p1.x = 0;
        p1.y = x;
        p2.x = width;
        p2.y = x;
        draw(vars, p1, p2, 0xFF0000);
        x += 3;
    }
    x = 0;
    while (x < width)
    {
        p1.x = x;
        p1.y = 0;
        p2.x = x;
        p2.y = height;
        draw(vars, p1, p2, 0x0000);
        x += 10;
    }
} */