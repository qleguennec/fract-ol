/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:37:54 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/09 16:48:16 by qle-guen         ###   ########.fr       */
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
	mlx_key_hook(fol->win, &fol_keys, fol);
	mlx_loop(fol->mlx);
}

void			fol_init(t_opts opts)
{
	t_fol			fol;
	static t_v2i	size = {700, 700};
	static char		*name = "fract'ol";

	ft_bzero(&fol, sizeof(fol));
	fol.size = size;
	fol.opts = opts;
	win_create(size, name, &fol);
	if (opts.set == MANDEL)
		set_mandel(size, fol.mlx, fol.win);
	else
		fol_exit("not implemented yet");
	mlx_run(&fol);
}
