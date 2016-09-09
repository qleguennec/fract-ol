/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mandel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:28:11 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/09 16:49:09 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include <stdlib.h>

static void		step(t_c *za, t_c zb, size_t *i)
{
	(*i)++;
	za->im = 2 * za->im * za->re + zb.im;
	za->re = za->re * za->re - za->im * za->im + zb.re;
}

void			set_mandel(t_v2i size, void *mlx, void *win)
{
	size_t		i;
	size_t		max = 10;
	t_v2i		v2;
	t_c			za;
	t_c			zb;

	v2.y = 0;
	while (v2.y < size.y)
	{
		v2.x = 0;
		while (v2.x < size.x)
		{
			za.re = (v2.x - size.x / 2) * 4.0 / size.x;
			za.im = (v2.y - size.y / 2) * 4.0 / size.y;
			zb.re = 0;
			zb.im = 0;
			i = 0;
			while (zb.re * zb.re + zb.im * zb.im <= 4 && i < max)
				step(&zb, za, &i);
			mlx_pixel_put(mlx, win, v2.x, v2.y, i < max ? C_WHITE : C_BLACK);
			v2.x++;
		}
		v2.y++;
	}
}
