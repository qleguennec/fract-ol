/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 16:25:46 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/10 23:11:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <math.h>

int			fol_ev_mouse(int button, int x, int y, t_view *v)
{
	if (!(button == 1 || button == 2))
		return (0);
	v->cx += (x - WIN_X_2) * v->scale;
	v->cy += (y - WIN_Y_2) * v->scale;
	if (button == 1 && v->scale > x * 1e-16 && v->scale > y * 1e-16)
		v->scale /= 2;
	else if (button == 2)
		v->scale *= 2;
	v->exp = 1;
	return (1);
}