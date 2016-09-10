/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mandel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:28:11 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/10 23:12:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>

#define M_MAX_ITER 256

static void		step(t_c *z, int *i)
{
	(*i)++;
	z[1].y = 2 * z[1].x * z[1].y + z[0].y;
	z[1].x = z[2].x - z[2].y + z[0].x;
	z[2].x = z[1].x * z[1].x;
	z[2].y = z[1].y * z[1].y;
}

static void		colorize(int *data, t_v2i lim)
{
	static int	sat = - 100;
	int			x;
	int			y;

	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			fill(*data, sat, lim, (t_rgb *)data);
			data++;
			x++;
		}
		y++;
	}
}

static void		run
	(t_view *v, int *data, t_v2i *lim)
{
	int			i;
	t_v2i		v2;
	t_c			z[3];

	v2.y = 0;
	while (v2.y < WIN_Y)
	{
		v2.x = 0;
		z[0].y = (v2.y - WIN_Y_2) * v->scale + v->cy;
		while (v2.x < WIN_X)
		{
			i = 0;
			z[0].x = (v2.x++ - WIN_X_2) * v->scale + v->cx;
			z[1].x = hypot(z[0].x - 0.25, z[0].y);
			if (z[0].x < z[1].x - 2 * z[1].x * z[1].x + 0.25
				|| (z[0].x + 1) * (z[0].x + 1) + z[0].y * z[0].y < 1/16)
				i = M_MAX_ITER;
			ft_bzero(&z[1], sizeof(*z) * 2);
			while (i < M_MAX_ITER && z[2].x + z[2].y < 4)
				step(z, &i);
			*lim = (t_v2i){MIN(lim->x, i), MAX(lim->y, i)};
			*data++ = i;
		}
		v2.y++;
	}
}

void		set_mandel
	(void *mlx, void *win, t_view *v)
{
	static void		*img = NULL;
	static int		*data = NULL;
	static t_v2i	lim = (t_v2i){M_MAX_ITER, 0};
	int				dummy;

	if (!img)
		img = mlx_new_image(mlx, WIN_X, WIN_Y);
	if (!data)
		data = (int *)mlx_get_data_addr(img, &dummy, &dummy, &dummy);
	run(v, data, &lim);
	colorize(data, lim);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}
