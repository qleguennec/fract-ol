/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 15:58:06 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include <stdlib.h>

int			fol_ev_keys(int keycode, t_fol *fol)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fol->mlx, fol->win);
		exit(0);
	}
	if (keycode == 15)
	{
		view_init(fol->view, fol->opts.set);
		fol->view->exp = 1;
	}
	return (0);
}
