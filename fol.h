/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:19:30 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/10 23:05:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOL_H
# define FOL_H

# include <stdio.h>

# define WIN_X		800
# define WIN_Y		800
# define WIN_X_2	WIN_X / 2
# define WIN_Y_2	WIN_Y / 2
# define JULIA		0
# define MANDEL		1
# define M_I_SCALE	1.0/256.0
# define M_I_CX		- .6
# define M_I_CY		0
# define C_BLACK	0x000000
# define C_WHITE	0xffffff

typedef struct			s_v2i
{
	int					x;
	int					y;
}						t_v2i;

typedef struct			s_c
{
	double				x;
	double				y;
}						t_c;

typedef struct			s_view
{
	double				cx;
	double				cy;
	double				scale;
	unsigned int		exp : 1;
}						t_view;

typedef struct			s_opts
{
	unsigned int		set : 2;
}						t_opts;

typedef struct			s_fol
{
	void				*mlx;
	void				*win;
	t_v2i				size;
	t_opts				opts;
	t_view				*view;
}						t_fol;

typedef struct			s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_rgb;

void					fol_exit(char *msg);
int						fol_loop(t_fol *fol);
void					fol_init(t_opts opts);
void					set_mandel(void *mlx, void *win, t_view *v);
int						fol_keys(int keycode, t_fol *fol);
int						fol_ev_keys(int keycode, t_fol *fol);
int						fol_ev_mouse(int button, int x, int y, t_view *v);
void					fill(int hue, int sat, t_v2i lim, t_rgb *p);

#endif
