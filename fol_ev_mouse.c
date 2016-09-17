/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 16:25:46 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/15 16:07:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <math.h>

int			fol_ev_mouse(int button, int x, int y, t_view *v)
{
	static double	scale_treshold = 1e-128;

	if (!(button == 1 || button == 2))
		return (0);
	if (button == 1
		&& v->scale.x > x * scale_treshold && v->scale.x > y * scale_treshold)
	{
		v->scale.x /= 2;
		v->scale.y = v->scale.x;
	}
	else if (button == 2)
	{
		v->scale.x *= 2;
		v->scale.y = v->scale.x;
	}
	v->cx.x += (x - WIN_X_2) * v->scale.x;
	v->cx.y = v->cx.x;
	v->cy.x += (y - WIN_Y_2) * v->scale.x;
	v->cy.y = v->cy.x;
	v->exp = 1;
	return (1);
}
