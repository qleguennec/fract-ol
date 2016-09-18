/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_constants.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 15:30:35 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:09:25 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_CONSTANTS_H
# define CL_CONSTANTS_H

# define MAX_ITER			500
# define V4					(double2){4.0, 4.0}
# define V_WIN_X_2			(double2){WIN_X_2, WIN_X_2}
# define V_WIN_Y_2			(double2){WIN_Y_2, WIN_Y_2}

typedef struct				s_view
{
	double2					ix;
	double2					iy;
	double2					cx;
	double2					cy;
	double2					scale;
	unsigned int			exp : 1;
	int						tex[IMG_LEN];
}							t_view;

#endif
