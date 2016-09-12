/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 16:25:46 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 23:08:12 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <math.h>

int			fol_ev_mouse(int button, int x, int y, t_view *v)
{
	static double	scale_treshold = 1e-64;

	if (!(button == 1 || button == 2))
		return (0);
	if (button == 1
		&& v->scale > x * scale_treshold && v->scale > y * scale_treshold)
		v->scale /= 2;
	else if (button == 2)
		v->scale *= 2;
	v->cx += (x - WIN_X_2) * v->scale;
	v->cy += (y - WIN_Y_2) * v->scale;
	v->exp = 1;
	return (1);
}
