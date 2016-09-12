/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 17:24:32 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 18:53:56 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"

int				fol_loop(t_fol *fol)
{
	if (!fol->view->exp)
		return (0);
//	if (fol->opts.set == MANDEL)
//		set_mandel(fol->mlx, fol->win, fol->view);
	fol->view->exp = 0;
	return (1);
}
