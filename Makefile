#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 12:38:39 by bazaluga          #+#    #+#              #
#    Updated: 2024/05/27 17:05:34 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	fdf

SRCDIR	    :=	src

OBJDIR	    :=	obj

INCDIR	    :=	include

LIBFTDIR    :=	$(INCDIR)/libft

LIBFT	    :=	$(LIBFTDIR)/libft.a

SRC	    :=  colors_utils.c display_utils.c end_handling.c events_handling.c \
		ft_atoi_forward.c ft_atou_base_forward.c ft_lstnew2.c ft_sign.c \
		garbage_collector.c line_drawing.c main.c map_parsing.c \
		point_handling.c

SRCMACOS    :=	mlx_compat_macos.c

SRCLINUX    :=	mlx_compat_linux.c

ifeq ($(shell uname), Linux)
	MLXDIR	    :=	$(INCDIR)/mlx_linux
	INCFLAGS    :=	-L$(LIBFTDIR) -lft -lXext -lX11 -lm
	SRC	    :=	$(SRC) $(SRCLINUX)

else
	MLXDIR	    :=	$(INCDIR)/mlx_macos
	INCFLAGS    :=	-L$(LIBFTDIR) -lft -framework OpenGL -framework AppKit -lm
	SRC	    :=	$(SRC) $(SRCMACOS)
endif

MLX	    :=  $(MLXDIR)/libmlx.a

OBJ	    :=  $(SRC:.c=.o)

SRC	    :=  $(addprefix $(SRCDIR)/, $(SRC))

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJ))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror -MMD -MP -g

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

$(OBJDIR):
		mkdir -p $(OBJDIR)

-include	$(OBJ:.o=.d)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c Makefile | $(OBJDIR)
		@echo $(GREEN)"COMPILING sources to objects"
		$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLXDIR) -c $< -o $@
		@echo $(RESET)

$(MLX):
		@echo $(GREEN)"\n\tCOMPILING MLX"$(RESET)
		@make -sC $(MLXDIR)
		@echo $(GREEN)"\n\tMLX COMPILED\n"$(RESET)

$(LIBFT):
		@echo $(GREEN)"\n\tCOMPILING LIBFT"$(RESET)
		@make -sC $(LIBFTDIR)
		@echo $(GREEN)"\n\tLIBFT COMPILED"$(RESET)

$(NAME):	$(OBJ) $(MLX) $(LIBFT)
		@echo $(GREEN)"LINKING objects to create $(NAME)"
		$(CC) $(OBJ) $(CFLAGS) -L$(MLXDIR) -lmlx $(INCFLAGS) -o $(NAME)
		@printf $(RESET)

clean:
		@echo $(RED)"CLEANING OBJS"
		rm -f $(OBJ)
		rm -f $(OBJ:.o=.d)
		@make -sC $(MLXDIR) clean
		@make -sC $(LIBFTDIR) clean
		@echo $(RESET)

fclean:		clean
		@echo $(RED)"CLEANING ALL"
		rm -f $(NAME)
		rm -rf *.dSYM
		@make -sC $(LIBFTDIR) fclean
		@echo $(RESET)

re:		fclean
		@make all

.PHONY:		all clean fclean re
