/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:37:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/10 21:48:53 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include "libft/libft.h"

static void		win_create(t_v2i size, char *name, t_fol *fol)
{
	if (!(fol->mlx = mlx_init()))
		fol_exit("error initializing mlx ptr");
	if (!(fol->win = mlx_new_window(fol->mlx, size.x, size.y, name)))
		fol_exit("error creating window");
}

static void		mlx_run(t_fol *fol)
{
	mlx_key_hook(fol->win, &fol_ev_keys, fol);
	mlx_mouse_hook(fol->win, &fol_ev_mouse, fol->view);
	mlx_loop_hook(fol->mlx, &fol_loop, fol);
	mlx_loop(fol->mlx);
}

static void		view_init(t_view *v)
{
	v->scale = M_I_SCALE;
	v->cx = M_I_CX;
	v->cy = M_I_CY;
	v->exp = 0;
}

void			fol_init(t_opts opts)
{
	t_fol			fol;
	t_view			view;
	static t_v2i	size = {WIN_X, WIN_Y};
	static char		*name = "fract'ol";

	ft_bzero(&fol, sizeof(fol));
	fol.size = size;
	fol.opts = opts;
	view_init(&view);
	fol.view = &view;
	win_create(size, name, &fol);
	if (opts.set == MANDEL)
		set_mandel(fol.mlx, fol.win, &view);
	else
		fol_exit("not implemented yet");
	mlx_run(&fol);
}
