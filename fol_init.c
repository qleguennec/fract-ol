/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:37:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:28:47 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "cl_helper.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"
#include "X.h"
#include <stddef.h>


static void		win_create(char *name, t_fol *fol)
{
	int		null;

	if (!(fol->mlx = mlx_init()))
		fol_exit("error initializing mlx ptr");
	if (!(fol->win = mlx_new_window(fol->mlx, WIN_X, WIN_Y, name)))
		fol_exit("error creating window");
	if (!(fol->img = mlx_new_image(fol->mlx, WIN_X, WIN_Y)))
		fol_exit("error allocating img");
	fol->tex = (int *)mlx_get_data_addr(fol->img, &null, &null, &null);
	ft_bzero(fol->tex, IMG_SIZE);
}

static void		mlx_run(t_fol *fol)
{
	mlx_key_hook(fol->win, &fol_ev_keys, fol);
	mlx_mouse_hook(fol->win, &fol_ev_mouse, fol);
	mlx_loop_hook(fol->mlx, &fol_loop, fol);
	mlx_hook(fol->win, MotionNotify, PointerMotionMask, &fol_ev_motion, fol);
	mlx_put_image_to_window(fol->mlx, fol->win, fol->img, 0, 0);
	mlx_loop(fol->mlx);
}

void			view_init(t_view *v, int set)
{
	static const int		iter_max[2] = {100, 100};
	static const double		ix[2] = {0, .285};
	static const double		iy[2] = {0, -.3};
	static const double		cx[2] = {-.7, 0};
	static const double		cy[2] = {0, 0};
	static const double		scale[2] = {1.0/256, 1.0/256};

	v->iter_max = iter_max[set];
	v->scale.x = scale[set];
	v->scale.y = v->scale.x;
	v->ix.x = ix[set];
	v->ix.y = v->ix.x;
	v->iy.x = iy[set];
	v->iy.y = v->iy.x;
	v->cx.x = cx[set];
	v->cx.y = v->cx.x;
	v->cy.x = cy[set];
	v->cy.y = v->cy.x;
	v->exp = 0;
}

void			fol_init(t_opts opts)
{
	t_fol			fol;
	t_view			view;
	t_cl_info		cl_i;

	ft_bzero(&fol, sizeof(fol));
	fol.opts = opts;
	view_init(&view, opts.set);
	fol.view = &view;
	cl_init(&cl_i, &view, sizeof(view));
	if (opts.set == MANDEL)
		cl_build_mandel(&cl_i);
	else if (opts.set == JULIA)
		cl_build_julia(&cl_i);
	win_create(WIN_NAME, &fol);
	cl_exec(&cl_i);
	cl_read(&cl_i, offsetof(t_view, tex), fol.tex, IMG_SIZE);
	fol.cl_i = &cl_i;
	mlx_run(&fol);
}
