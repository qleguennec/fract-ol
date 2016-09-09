/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 13:52:11 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/09 16:48:08 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fol.h"
#include "libft/libft.h"
#include <unistd.h>

static void			help(void)
{
	fol_exit("fractol -s[julia/mandel]");
}

static t_opts		parse_args(int argc, char **argv)
{
	t_opts			opts;

	ft_bzero(&opts, sizeof(opts));
	if (argc < 2)
		help();
	if (argv[1][0] == '-')
	{
		if (argv[1][1] == 's')
		{
			if (!ft_strcmp(&argv[1][2], "julia"))
				opts.set = JULIA;
			else if (!ft_strcmp(&argv[1][2], "mandel"))
				opts.set = MANDEL;
			else
				help();
		}
		else
			help();
	}
	else
		help();
	return (opts);
}

int					main(int argc, char **argv)
{
	t_opts			opts;

	opts = parse_args(argc, argv);
	fol_init(opts);
	return (0);
}
