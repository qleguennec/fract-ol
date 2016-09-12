/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 15:18:43 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 20:50:45 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_helper.h"
#include "fol.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static char	*cl_read_source(char *filename)
{
	char	buf[CL_SRC_SIZE];
	char	*err;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		err = strerror(fd);
		write(1, err, ft_strlen(err));
		exit(fd);
	}
	ft_bzero(buf, CL_SRC_SIZE);
	fd = read(fd, buf, CL_SRC_SIZE);
	if (fd < 0)
	{
		err = strerror(fd);
		write(1, err, ft_strlen(err));
		exit(fd);
	}
	return (ft_strdup(buf));
}

void		cl_init(t_cl_info *cl_i, void *data, size_t data_size)
{
	clGetPlatformIDs(1, &cl_i->pl_id, NULL);
	clGetDeviceIDs(cl_i->pl_id
		, CL_DEVICE_TYPE_GPU, 1, &cl_i->dev_id, &cl_i->dev_num);
	cl_i->ctxt = clCreateContext(NULL, 1, &cl_i->dev_id, NULL, NULL, NULL);
	cl_i->cmd_queue = clCreateCommandQueue(cl_i->ctxt, cl_i->dev_id, 0, NULL);
	cl_i->mem = clCreateBuffer(cl_i->ctxt
		, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, data_size, data, NULL);
}

void		cl_build(t_cl_info *cl_i, char *filename, char *kernel_func)
{
	char	log[CL_LOG_SIZE];
	char	malloc_err[] = "unable to allocate memory for program source";
	char	*prgsrc;
	int		err;

	prgsrc = cl_read_source(filename);
	if (!prgsrc)
	{
		write(1, malloc_err, ft_strlen(malloc_err));
		exit(1);
	}
	cl_i->prog = clCreateProgramWithSource(cl_i->ctxt, 1
		, (const char **)&prgsrc, NULL, NULL);
	err = clBuildProgram(cl_i->prog, cl_i->dev_num
		, &cl_i->dev_id, "-I.", NULL, NULL);
	if (err < 0)
	{
		clGetProgramBuildInfo(cl_i->prog, cl_i->dev_id, CL_PROGRAM_BUILD_LOG
			, CL_LOG_SIZE, log, NULL);
		write(1, log, ft_strlen(log));
		exit(1);
	}
	cl_i->kernel = clCreateKernel(cl_i->prog, kernel_func, &err);
	clSetKernelArg(cl_i->kernel, 0, sizeof(cl_mem), &cl_i->mem);
}

void		cl_exec(t_cl_info *cl_i)
{
	size_t		max_work_size;
	cl_event	ev;

	clGetDeviceInfo(cl_i->dev_id, CL_DEVICE_MAX_WORK_GROUP_SIZE
		, sizeof(max_work_size), &max_work_size, NULL);
	clEnqueueNDRangeKernel(cl_i->cmd_queue
		, cl_i->kernel
		, 1
		, NULL
		, (const size_t [1]){WIN_X * WIN_Y}
		, (const size_t [1]){600}
		, 0
		, NULL
		, &ev);
	clWaitForEvents(CL_COMPLETE, &ev);
}

void		cl_read
	(t_cl_info *cl_i, size_t offset, void *data, size_t data_size)
{
	clEnqueueReadBuffer(cl_i->cmd_queue, cl_i->mem, CL_TRUE
		, offset, data_size, data, 0, NULL, NULL);
}
