#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/07 12:38:39 by bazaluga          #+#    #+#              #
#    Updated: 2024/05/08 11:03:47 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	:=	fdf

SRCDIR	:=	src

OBJDIR	:=	obj

INCDIR	:=	include

ifeq ($(shell uname), Linux)
	MLXDIR		:=	mlx_linux
	INCFLAGS	:=	-lXext -lX11
else
	MLXDIR		:=	mlx_macos
	INCFLAGS	:=	-framework OpenGL -framework AppKit
endif

MLX	:=	$(MLXDIR)/libmlx.a

SRC		:=	test.c

OBJ		:=	$(SRC:.c=.o)

SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

OBJ		:=	$(addprefix $(OBJDIR)/, $(OBJ))

CC		:=	cc

CFLAGS	:=	-Wall -Wextra -Werror -MMD

########### COLORS ##########

RED		:=	"\033[1;31m"
GREEN	:=	"\033[1;32m"
RESET	:=	"\033[0m"

all:			$(NAME)

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

$(NAME):		$(OBJ) $(MLX)
				@echo $(GREEN)"LINKING objects to create $(NAME)"
				$(CC) $(OBJ) -L$(MLXDIR) -lmlx $(INCFLAGS) -o $(NAME)
				@printf $(RESET)

clean:
				@echo $(RED)"CLEANING OBJS"
				rm -f $(OBJ)
				rm -f $(OBJ:.o=.d)
				make -sC $(MLXDIR) clean
				@echo $(RESET)

fclean:			clean
				@echo $(RED)"CLEANING ALL"
				rm -f $(NAME)
				rm -rf *.dSYM
				@echo $(RESET)

re:				fclean
				@make all

.PHONY:			all clean fclean re

-include:		$(OBJ:.o=.d)
