/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:37:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/15 16:42:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "cl_helper.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"
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
	mlx_mouse_hook(fol->win, &fol_ev_mouse, fol->view);
	mlx_loop_hook(fol->mlx, &fol_loop, fol);
	mlx_put_image_to_window(fol->mlx, fol->win, fol->img, 0, 0);
	mlx_loop(fol->mlx);
}

static void		view_init(t_view *v)
{
	v->scale.x = M_I_SCALE;
	v->scale.y = M_I_SCALE;
	v->cx.x = M_I_CX;
	v->cx.y = M_I_CX;
	v->cy.x = M_I_CY;
	v->cy.y = M_I_CY;
	v->exp = 0;
}

void			fol_init(t_opts opts)
{
	t_fol			fol;
	t_view			view;
	t_cl_info		cl_i;

	ft_bzero(&fol, sizeof(fol));
	fol.opts = opts;
	view_init(&view);
	fol.view = &view;
	cl_init(&cl_i, &view, sizeof(view));
	if (opts.set == MANDEL)
		cl_build_mandel(&cl_i);
	win_create(WIN_NAME, &fol);
	cl_exec(&cl_i);
	cl_read(&cl_i, offsetof(t_view, tex), fol.tex, IMG_SIZE);
	fol.cl_i = &cl_i;
	mlx_run(&fol);
}
