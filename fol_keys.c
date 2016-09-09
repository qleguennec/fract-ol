/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/09 16:14:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libmlx/mlx.h"
#include <stdlib.h>

int			fol_keys(int keycode, t_fol *fol)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fol->mlx, fol->win);
		exit(0);
	}
	return (0);
}
