/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read_prgsrc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:06:03 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/17 15:02:44 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgnl/libgnl.h"
#include "libvect/libvect.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>

static int	validate(t_vect *line, size_t i)
{
	if (i == line->used)
		return (0);
	if (i + 2 <= line->used 
		&& (!ft_memcmp(line->data + i, "/*", 2)
			|| !ft_memcmp(line->data + i, "*/", 2)))
		return (0);
	return (1);
}

char		*cl_read_prgsrc(char *filename, t_vect *gnl)
{
	t_vect	line;
	size_t	i;
	int		ret;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	ft_bzero(&line, sizeof(line));
	i = 0;
	while ((ret = get_next_line(fd, gnl, &line)) != 0)
	{
		if (ret < 0)
			return (NULL);
		if (i == line.used)
			continue ;
		if (!validate(&line, i))
			line.used = i;
		else
		{
			vect_mset_end(&line, '\n', 1);
			i = line.used;
		}
	}
	vect_mset_end(&line, '\0', 1);
	return (line.data);
}
