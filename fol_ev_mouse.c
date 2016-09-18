/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 16:25:46 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:14:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <math.h>

static int	mandel(int button, int x, int y, t_view *v)
{
	v->exp = 1;
	v->cx.x += (x - WIN_X_2) * v->scale.x;
	v->cx.y = v->cx.x;
	v->cy.x += (y - WIN_Y_2) * v->scale.x;
	v->cy.y = v->cy.x;
	if (button == 1)
	{
		v->scale.x /= SF;
		v->scale.y = v->scale.x;
	}
	else if (button == 2)
	{
		v->scale.x *= SF;
		v->scale.y = v->scale.x;
	}
	return (1);
}

int			fol_ev_mouse(int button, int x, int y, t_fol *fol)
{
	if (!(button == 1 || button == 2))
		return (0);
	if (fol->opts.set == MANDEL)
		return (mandel(button, x, y, fol->view));
	else if (fol->opts.set == JULIA)
		return (mandel(button, x, y, fol->view));
	return (1);
}
