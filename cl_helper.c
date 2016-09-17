/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 15:18:43 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/15 15:01:56 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_helper.h"
#include "fol.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

void		cl_build
	(t_cl_info *cl_i, char *prgsrc, char *kernel_func, char *build_options)
{
	char	log[CL_LOG_SIZE];
	char	err_msg[] = "unable to read program source";
	int		err;

	if (!prgsrc)
	{
		write(1, err_msg, sizeof(err_msg));
		exit(1);
	}
	cl_i->prog = clCreateProgramWithSource(cl_i->ctxt, 1
		, (const char **)&prgsrc, NULL, NULL);
	err = clBuildProgram(cl_i->prog, cl_i->dev_num
		, &cl_i->dev_id
		, build_options
		, NULL, NULL);
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
	clock_t		start;
	clock_t		end;
	double		elapsed;
	size_t		global;
	size_t		local;
	cl_int		ret;

	global = WIN_Y;
	local = WIN_Y;
	start = clock();
	ret = clEnqueueNDRangeKernel(cl_i->cmd_queue
		, cl_i->kernel
		, 1
		, NULL
		, &global
		, &local
		, 0
		, NULL
		, NULL);
	clFinish(cl_i->cmd_queue);
	end = clock();
	elapsed = (end-start)/(double)CLOCKS_PER_SEC;
	printf("compute time: %lf\n", elapsed);
}

void		cl_read
	(t_cl_info *cl_i, size_t offset, void *data, size_t data_size)
{
	clock_t		start;
	clock_t		end;
	double		elapsed;

	start = clock();
	clEnqueueReadBuffer(cl_i->cmd_queue, cl_i->mem, CL_TRUE
		, offset, data_size, data, 0, NULL, NULL);
	end = clock();
	elapsed = (end-start)/(double)CLOCKS_PER_SEC;
	printf("read time: %lf\n", elapsed);
}
