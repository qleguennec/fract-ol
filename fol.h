/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 14:19:30 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/09 16:41:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOL_H
# define FOL_H

# include <stdio.h>

# define JULIA		0
# define MANDEL		1
# define C_BLACK	0x000000
# define C_WHITE	0xffffff

typedef struct			s_v2i
{
	int					x;
	int					y;
}						t_v2i;

typedef struct			s_c
{
	double				re;
	double				im;
}						t_c;

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
}						t_fol;

void					fol_exit(char *msg);
void					fol_init(t_opts opts);
void					set_mandel(t_v2i size, void *mlx, void *win);
int						fol_keys(int keycode, t_fol *fol);

#endif
