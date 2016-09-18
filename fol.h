/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:19:30 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/18 18:13:28 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOL_H
# define FOL_H

# define WIN_X		1024
# define WIN_Y		768
# define WIN_NAME	"fractol"
# define WIN_X_2	WIN_X / 2
# define WIN_Y_2	WIN_Y / 2
# define IMG_LEN	WIN_X * WIN_Y
# define IMG_SIZE	IMG_LEN * 4
# define SF			2.0
# define MANDEL		0
# define JULIA		1
# define M_CL_SRC	"mandel.cl"
# define M_CL_MAIN	"mandel"
# define J_CL_SRC	"julia.cl"
# define J_CL_MAIN	"julia"
# define C_WHITE	0xfffffff
# define C_BLACK	0

# include "cl_helper.h"
# include "libvect/libvect.h"
# include <OpenCL/opencl.h>

typedef struct				s_view
{
	cl_double2				ix;
	cl_double2				iy;
	cl_double2				cx;
	cl_double2				cy;
	cl_double2				scale;
	unsigned int			exp : 1;
	int						tex[IMG_LEN];
}							t_view;

typedef struct				s_opts
{
	unsigned int			set : 2;
}							t_opts;

typedef struct				s_fol
{
	void					*mlx;
	void					*win;
	void					*img;
	int						*tex;
	t_opts					opts;
	t_view					*view;
	t_cl_info				*cl_i;
}							t_fol;

void						fol_exit(char *msg);
int							fol_loop(t_fol *fol);
void						fol_init(t_opts opts);
void						set_mandel(void *mlx, void *win, t_view *v);
int							fol_keys(int keycode, t_fol *fol);
int							fol_ev_keys(int keycode, t_fol *fol);
int							fol_ev_mouse(int button, int x, int y, t_fol *fol);
int							fol_ev_motion(int x, int y, t_fol *fol);
void						mlx_send_tex(int *src, int *dest);
void						cl_build_mandel(t_cl_info *cl_i);
void						cl_build_julia(t_cl_info *cl_i);
char						*cl_read_prgsrc(char *filename, t_vect *gnl);
void						view_init(t_view *v, int set);

#endif
