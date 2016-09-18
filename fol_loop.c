/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 17:24:32 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:05:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "cl_helper.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"
#include <stddef.h>
#include <time.h>
#include <stdio.h>

static int		redraw(t_fol *fol)
{
	mlx_clear_window(fol->mlx, fol->win);
	cl_exec(fol->cl_i);
	cl_read(fol->cl_i, offsetof(t_view, tex), fol->tex, IMG_SIZE);
	mlx_put_image_to_window(fol->mlx, fol->win, fol->img, 0, 0);
	return (1);
}

static int		update_cl_buffer(t_fol *fol, t_cl_info *cl_i)
{
	size_t		write_size;

	write_size = offsetof(t_view, scale) + sizeof(cl_double2);
	clEnqueueWriteBuffer(cl_i->cmd_queue
		, cl_i->mem
		, CL_TRUE
		, 0
		, write_size
		, fol->view
		, 0
		, NULL
		, NULL);
	return (1);
}

int				fol_loop(t_fol *fol)
{
	if (!fol->view->exp)
		return (0);
	fol->view->exp = 0;
	return (update_cl_buffer(fol, fol->cl_i) && redraw(fol));
}
