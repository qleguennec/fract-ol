/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 16:41:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:17:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include <math.h>

static int	mandel(int x, int y, t_view *view)
{
	(void)x;
	(void)y;
	(void)view;
	return (0);
}

static int	julia(int x, int y, t_view *v)
{
	v->exp = 1;
	v->ix.x = hypot((x - WIN_X_2), (y - WIN_X_2)) / WIN_X;
	v->ix.y = v->ix.x;
	v->iy.x = hypot((y - WIN_Y_2), (x - WIN_X_2)) / WIN_Y;
	v->iy.y = v->iy.x;
	return (1);
}

int			fol_ev_motion(int x, int y, t_fol *fol)
{
	if (fol->opts.set == MANDEL)
		return (mandel(x, y, fol->view));
	else if (fol->opts.set == JULIA)
		return (julia(x, y, fol->view));
	return (0);
}
