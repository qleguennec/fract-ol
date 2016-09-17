/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 00:31:51 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 00:31:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_constants.h"
#define MAX_ITER 250

constant double2 v4 = {4.0, 4.0};
constant double2 win_x = {WIN_X_2, WIN_X_2};
constant double2 win_y = {WIN_Y_2, WIN_Y_2};

void				color(global unsigned char *out, int i)
{
	double		c;

	c = log((double)i) / log((double)MAX_ITER);
	if (c < 1)
	{
		out[0] = 0;
		out[1] = 0;
		out[2] = 255 * c;
		out[3] = 0;
	}
	else if ( c < 2 )
	{
		out[0] = 0;
		out[1] = 0;
		out[2] = 255 * (c - 1);
		out[3] = 255;
	}
	else
	{
		out[0] = 0;
		out[1] = 0;
		out[2] = 255 * (c - 2);
		out[3] = 255;
	}
}

kernel void			mandel(global t_view *v)
{
	double2		vr;
	double2		vi;
	double2		zr;
	double2		zi;
	double2		tr;
	double2		ti;
	double2		zz;
	long2		delta;
	global int	*out;
	int			x;
	int			y;
	int			i;
	int			j;

	x = 0;
	y = get_local_id(0);
	vi = (double2){y, y};
	vi = (vi - win_y) * v->scale + v->cy;
	out = v->tex + y * WIN_X;
	while (x < WIN_X)
	{
		vr = (double2){x, x + 1};
		vr = (vr - win_x) * v->scale + v->cx;
		zr = vr;
		zi = vi;
		tr = vr * vr;
		ti = vi * vi;
		i = 1;
		j = 1;
		delta = (long2){1, 1};
		while ((delta.x && i < MAX_ITER && ++i)
			|| (delta.y && j < MAX_ITER && ++j))
		{
			zz = zr * zi;
			zr = tr - ti + vr;
			zi = zz + zz + vi;
			tr = zr * zr;
			ti = zi * zi;
			delta = islessequal(tr + ti, v4);
		}
		if (i == MAX_ITER)
			out[x++] = C_BLACK;
		else
			color(out + x++, i);
		if (j == MAX_ITER)
			out[x++] = C_BLACK;
		else
			color(out + x++, j);
	}
}
