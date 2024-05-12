#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 12:38:39 by bazaluga          #+#    #+#              #
#    Updated: 2024/05/12 19:50:57 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	fdf

SRCDIR	    :=	src

OBJDIR	    :=	obj

INCDIR	    :=	include

LIBFTDIR    :=	$(INCDIR)/libft

LIBFT	    :=	$(LIBFTDIR)/libft.a

ifeq ($(shell uname), Linux)
	MLXDIR	    :=	$(INCDIR)/mlx_linux
	INCFLAGS    :=	-lXext -lX11

else
	MLXDIR	    :=	$(INCDIR)/mlx_macos
	INCFLAGS    :=	-framework OpenGL -framework AppKit
endif

MLX	    :=  $(MLXDIR)/libmlx.a

SRC	    :=  test.c

OBJ	    :=  $(SRC:.c=.o)

SRC	    :=  $(addprefix $(SRCDIR)/, $(SRC))

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJ))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror -MMD

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

$(OBJDIR):
		mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
		@echo $(GREEN)"COMPILING sources to objects"
		$(CC) $(CFLAGS) -I$(MLXDIR) -c $< -o $@
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
		$(CC) $(OBJ) -L$(MLXDIR) -lmlx $(INCFLAGS) -o $(NAME)
		@printf $(RESET)

clean:
		@echo $(RED)"CLEANING OBJS"
		rm -f $(OBJ)
		rm -f $(OBJ:.o=.d)
		make -sC $(MLXDIR) clean
		@echo $(RESET)

fclean:		clean
		@echo $(RED)"CLEANING ALL"
		rm -f $(NAME)
		rm -rf *.dSYM
		@echo $(RESET)

re:		fclean
		@make all

.PHONY:		all clean fclean re

-include:	$(OBJ:.o=.d)
