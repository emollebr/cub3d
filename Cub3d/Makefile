# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 17:14:16 by lejimene          #+#    #+#              #
#    Updated: 2024/01/07 17:50:32 by lejimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c
OFILES = $(CFILES:.c=.o)
NAME = cub3d
SRC = sources
LIB = cub3d.a
HPATH = includes
MLXFLAGS = -I ./includes/ -I ./minilibx-linux -lXext -lX11 -lm
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
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