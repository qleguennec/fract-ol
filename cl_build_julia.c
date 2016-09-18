/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_build_julia.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:51:53 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 15:50:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "cl_helper.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"

static void		set_build_opts(t_vect *v)
{
	vect_fmt(v, "-I. ");
	vect_fmt(v, "-D WIN_X=%d ", WIN_X);
	vect_fmt(v, "-D WIN_Y=%d ", WIN_Y);
	vect_fmt(v, "-D WIN_X_2=%d ", WIN_X_2);
	vect_fmt(v, "-D WIN_Y_2=%d ", WIN_Y_2);
	vect_fmt(v, "-D IMG_LEN=%d ", WIN_X * WIN_Y);
	vect_fmt(v, "-D C_BLACK=%#x ", C_BLACK);
	vect_fmt(v, "-D C_WHITE=%#x ", C_WHITE);
	vect_mset_end(v, '\0', 1);
}

void			cl_build_julia(t_cl_info *cl_i)
{
	t_vect	vect;
	char	*prgsrc;

	ft_bzero(&vect, sizeof(vect));
	prgsrc = cl_read_prgsrc(J_CL_SRC, &vect);
	vect.used = 0;
	set_build_opts(&vect);
	cl_build(cl_i, prgsrc, J_CL_MAIN, vect.data);
}
