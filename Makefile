# Directories
PROJECT		=	fract-ol
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/fractol

# Compiler options
CC			=	clang
CFLAGS		=	$(addprefix -I,$(INCLUDE)) -Wall -Wextra -Werror -g -O3

# Color output
BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

SRC += cl_build_julia.c
SRC += cl_build_mandel.c
SRC += cl_helper.c
SRC += cl_read_prgsrc.c
SRC += fol_ev_keys.c
SRC += fol_ev_motion.c
SRC += fol_ev_mouse.c
SRC += fol_exit.c
SRC += fol_init.c
SRC += fol_loop.c
SRC += main.c

LIB += libvect.a
LIB += libprintf.a
LIB += libgnl.a
LIB += libft.a

MLXDIR		=	libmlx
MLXNAME		=	libmlx.a
MLX			=	$(MLXDIR)/$(MLXNAME)
MLXFLAGS	=	-framework OpenGL -framework AppKit -L$(MLXDIR) -framework OpenCL

OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))
LIBRARIES	=	$(addprefix $(BUILDDIR)/, $(LIB)) $(MLX)
LIBLINK		+=	$(addprefix -l, $(LIB:lib%.a=%))
LIBLINK		+=	$(addprefix -l, $(MLXNAME:lib%.a=%))

all: $(NAME)

$(MLX): $(MLXDIR)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	make -C $(MLXDIR)

$(BUILDDIR)/%.a: %
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	BINDIR=$(CURDIR)/$(BUILDDIR) BUILDDIR=$(CURDIR)/$(BUILDDIR) \
		   make --no-print-directory -C $<

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBRARIES)
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	@$(CC) $(CFLAGS) $(MLXFLAGS) -L$(BUILDDIR) $(LIBLINK) $(OBJECTS) $(LIBLINK) -o $(NAME)
	@echo "OK\t"$(NAME)

.PHONY: clean fclean re

clean:
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	rm -rf $(OBJECTS)

fclean: clean
	@printf $(BLUE)$(PROJECT)$(END)'\t'
	rm -rf $(BUILDDIR)
	rm -rf $(NAME)

re: fclean all
