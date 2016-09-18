/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 00:31:51 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 00:31:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_constants.h"

static unsigned int		color(int i)
{
	double			c;
	unsigned char	out[4];

	c = log((double)i) / log((double)MAX_ITER);
	((int *)out)[0] = 0;
	if (c < 1)
		out[2] = 255 * c;
	else if ( c < 2 )
	{
		out[2] = 255 * (c - 1);
		out[3] = 255;
	}
	else
	{
		out[2] = 255 * (c - 2);
		out[3] = 255;
	}
	return (((unsigned int *)out)[0]);
}

static void				julia_step
	(double2 *z, long2 *delta, double2 ix, double2 iy)
{
	z[6] = z[2] * z[3];
	z[2] = z[4] - z[5] + ix;
	z[3] = z[6] + z[6] + iy;
	z[4] = z[2] * z[2];
	z[5] = z[3] * z[3];
	*delta = islessequal(z[4] + z[5], V4);
}

kernel void				julia(global t_view *v)
{
	double2		z[7];
	long2		delta;
	global int	*out;
	int2		a;
	int			i;

	a = (int2){0, get_local_id(0)};
	z[1] = ((double2){a.y, a.y} - V_WIN_Y_2) * v->scale + v->cy;
	out = v->tex + a.y * WIN_X;
	while (a.x < WIN_X)
	{
		z[0] = ((double2){a.x, a.x + 1} - V_WIN_X_2) * v->scale + v->cx;
		z[2] = z[0];
		z[3] = z[1];
		z[4] = z[2] * z[2];
		z[5] = z[3] * z[3];
		i = 1;
		delta = (long2){1, 1};
		while ((delta.x || delta.y) && ++i < MAX_ITER)
			julia_step(z, &delta, v->ix, v->iy);
		out[a.x++] = delta.x ? C_BLACK : color(i);
		out[a.x++] = delta.y ? C_BLACK : color(i);
	}
}
