/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_ev_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/15 15:45:21 by qle-guen         ###   ########.fr       */
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
		fol->view->scale.x = M_I_SCALE;
		fol->view->scale.y = M_I_SCALE;
		fol->view->cx.x = M_I_CX;
		fol->view->cx.y = M_I_CX;
		fol->view->cy.x = M_I_CY;
		fol->view->cy.y = M_I_CY;
		fol->view->exp = 1;
	}
	return (0);
}
