/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 18:24:58 by qle-guen          #+#    #+#             */
/*   Updated: 2016/09/12 01:04:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_HELPER_H
# define CL_HELPER_H

# define CL_SRC_SIZE			20480
# define CL_LOG_SIZE			20480

# include <OpenCL/opencl.h>

typedef struct			s_cl_info
{
	cl_platform_id		pl_id;
	cl_device_id		dev_id;
	cl_context			ctxt;
	cl_command_queue	cmd_queue;
	cl_mem				mem;
	cl_program			prog;
	cl_kernel			kernel;
	cl_uint				dev_num;
}						t_cl_info;

void					cl_init(t_cl_info *cl_i, void *data, size_t data_size);
void					cl_build(t_cl_info *cl_i, char *filename, char *kernel_func);
void					cl_exec(t_cl_info *cl_i);
void					cl_read(t_cl_info *cl_i, size_t offset, void *data, size_t data_size);


#endif
