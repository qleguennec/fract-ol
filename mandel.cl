/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 00:31:51 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 00:31:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"

#define MAX_TER	50

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
		while (iter < MAX_TER && zs.x + zs.y < 4)
		{
			z.y = 2 * z.x * z.y + zc.y;
			z.x = zs.x - zs.y + zc.x;
			zs = z * z;
			iter++;
		}
		v->tex[i.y * WIN_Y + i.x++] = iter < MAX_TER ? C_WHITE : C_BLACK;
	}
}
