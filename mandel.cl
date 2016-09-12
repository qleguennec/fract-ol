/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 00:31:51 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 00:31:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"

kernel void			fill_blank(global t_view *v)
{
	int		x;
	int		y;

	x = 0;
	y = get_local_id(0);
	while (x < WIN_X)
		v->tex[y * WIN_X + x++] = C_WHITE;
}
