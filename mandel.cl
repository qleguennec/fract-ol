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

#include "fol.h"

#define MAX_ITER	100

static void			color(global int *px, int iter)
{
	double		c;

	if (iter == MAX_ITER)
		*px = C_BLACK;
	else
	{
		if ((c = 3 * log((double)iter) / log(MAX_ITER - 1.0)) < 1)
			*px = 255 * (c - 1);
		else if (c < 2)
			*px = 255 * c;
		else
			*px = 255 * (c + 1);
	}
}

kernel void			mandel(global t_view *v)
{
	int2		i;
	double2		z;
	double2		zs;
	double2		zc;
	int			iter;

	i.x = 0;
	i.y = get_local_id(0);
	zc.y = (i.y - WIN_Y_2) * v->scale + v->cy;
	while (i.x < WIN_X)
	{
		iter = 0;
		z = (double2)(0, 0);
		zs = (double2)(0, 0);
		zc.x = (i.x - WIN_X_2) * v->scale + v->cx;
		while (iter < MAX_ITER && zs.x + zs.y < 4)
		{
			z.y = 2 * z.x * z.y + zc.y;
			z.x = zs.x - zs.y + zc.x;
			zs = z * z;
			iter++;
		}
		color(v->tex + (i.y * WIN_X + i.x++), iter);
	}
}
