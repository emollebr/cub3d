# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: levijimenezrufes <levijimenezrufes@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 17:14:16 by lejimene          #+#    #+#              #
#    Updated: 2024/01/09 16:18:50 by levijimenez      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
CFILES = main.c
OFILES = $(CFILES:.c=.o)
NAME = cub3d
SRC = sources
LIB = cub3d.a
HPATH = includes
<<<<<<< HEAD
MLXFLAGS = -I ./includes/ -I ./minilibx-linux -I ./libft -lXext -lX11 -lm
MLX_NAME	= libmlx.a
MLX_PATH = minilibx-linux/
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
=======
MLXFLAGS = -Lmlx -lmlx -L$(MLX_PATH) -framework OpenGL -framework AppKit
MLX_PATH	= ./minilibx_macos/
MLX_NAME	= libmlx.a
>>>>>>> 12d417344314f79014c5bc3d36ea69aa60b82364
MLX			= $(MLX_PATH)$(MLX_NAME)

all : $(NAME)

$(NAME) : $(OFILES)
	@${CC} $^ -o $@ $(MLX) ${MLXFLAGS}
	@ar -r $(LIB) $(OFILES)

$(SRC)/%.o: $(SRC)/%.c $(HPATH)/%.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${NAME}

fclean : clean
	@rm ${OFILES} $(LIB)

re : fclean all
