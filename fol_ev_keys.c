/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:57:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

int			fol_ev_keys(int keycode, t_fol *fol)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fol->mlx, fol->win);
		exit(0);
	}
	fol->view->exp = 1;
	if (keycode == 15)
		view_init(fol->view, fol->opts.set);
	if (keycode == 69)
		fol->view->iter_max += DI;
	if (keycode == 78)
		fol->view->iter_max -= DI;
	return (0);
}
