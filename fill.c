/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 21:58:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/10 23:05:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <math.h>

static void		col_hsv_rgb(t_rgb *p, int sat, int h)
{
	double		c;
	double		x;

	c = 255 * sat;
	x = c * ((1 - ABS(fmod(h, 2) - 1)));
	if (h == 0 && ((p->r = c) || 1))
		p->g = x;
	else if (h == 1 && ((p->r = x) || 1))
		p->g = c;
	else if (h == 2 && ((p->g = c) || 1))
		p->b = x;
	else if (h == 3 && ((p->g = x) || 1))
		p->b = c;
	else if (h == 4 && ((p->r = x) || 1))
		p->b = c;
	else
	{
		p->r = c;
		p->b = x;
	}
}

void			fill(int hue, int sat, t_v2i lim, t_rgb *p)
{
	if (lim.x == lim.y)
		lim.y = lim.x + 1;
	if (!sat)
	{
		p->r = 255 * (lim.y - hue) / (lim.y - lim.x);
		p->g = p->r;
		p->g = p->r;
	}
	col_hsv_rgb(p, sat, fmod(1e-4 + 4.0 * (hue - lim.x) / (lim.y - lim.x), 6));
}
