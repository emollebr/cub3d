# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 17:14:16 by lejimene          #+#    #+#              #
#    Updated: 2024/01/25 18:46:18 by emollebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fPIE
CFILES = main.c \
		image.c \
		doors.c \
		sprites.c \
		parse_cub_file.c \
		parse_map.c \
		utils_parse_map.c \
		utils_parse_map_2.c \
		parse_textures.c \
		minimap.c \
		cast_rays.c \
		draw.c \
		key_events.c \
		utils_textures.c \
		utils_colors.c
OFILES = $(CFILES:.c=.o)
NAME = cub3d
SRC = sources
LIB = cub3d.a
HPATH = includes
MLXFLAGS = -I ./includes/ -I ./minilibx-linux -I./libft -L./libft -lXext -lX11 -lm
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
LIBFT		= ./libft/libft.a

all : $(NAME)

$(NAME) : $(OFILES)
	@${CC} $^ -o $@ $(LIBFT) $(MLX) ${MLXFLAGS}
	@ar -r $(LIB) $(OFILES)

$(SRC)/%.o: $(SRC)/%.c $(HPATH)/%.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${OFILES}

fclean : clean
	@rm ${NAME} $(LIB)

re : fclean all
