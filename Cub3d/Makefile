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
CFLAGS = -g -Wall -Wextra -Werror
CFILES = main.c parse_cub_file.c parse_map.c parse_textures.c
OFILES = $(CFILES:.c=.o)
NAME = cub3d
SRC = sources
LIB = cub3d.a
HPATH = includes
MLXFLAGS =  -Lmlx -lmlx -L$(MLX_PATH) -framework OpenGL -framework AppKit
MLX_PATH	= ./minilibx_macos/
MLX_NAME	= libmlx.a
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
MLX			= $(MLX_PATH)$(MLX_NAME)
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

all : $(NAME)

$(NAME) : $(OFILES)
	@${CC} $^ -o $@ $(MLX) $(LIBFT) ${MLXFLAGS}
	@ar -r $(LIB) $(OFILES)

$(SRC)/%.o: $(SRC)/%.c $(HPATH)/%.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${NAME}

fclean : clean
	@rm ${OFILES} $(LIB)

re : fclean all