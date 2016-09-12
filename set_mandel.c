/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mandel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 15:28:11 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 17:34:05 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>
#include <OpenCL/OpenCL.h>

#define M_MAX_ITER 1000

static void		colorize(int *data, t_v2i lim)
{
	static int	sat = 2000;
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

void		set_mandel
	(void *mlx, void *win, t_view *v)
{
	static void		*img = NULL;
	static int		*data = NULL;
	static t_v2i	lim = (t_v2i){0, M_MAX_ITER};
	int				dummy;

	if (!img)
		img = mlx_new_image(mlx, WIN_X, WIN_Y);
	if (!data)
		data = (int *)mlx_get_data_addr(img, &dummy, &dummy, &dummy);
	render(v, data, &lim);
	lim.y += 1;
	colorize(data, lim);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}
