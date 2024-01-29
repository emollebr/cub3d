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
CFLAGS = -g -Wall -Wextra -Werror
CFILES =  $(SRC)/main.c \
	$(SRC)/image.c \
	 $(SRC)/doors.c \
	$(SRC)/sprites.c \
	$(SRC)/parse_cub_file.c \
	 $(SRC)/parse_map.c \
	 $(SRC)/utils_parse_map.c \
	 $(SRC)/utils_parse_map_2.c \
	 $(SRC)/parse_textures.c \
	 $(SRC)/minimap.c \
	 $(SRC)/cast_rays.c \
	 $(SRC)/draw.c \
	 $(SRC)/key_events.c \
	 $(SRC)/utils_textures.c \
	 $(SRC)/utils_minimap.c \
	 $(SRC)/utils_colors.c \
	 $(SRC)/sprites_utils.c \
	 $(SRC)/player_move.c \
	 $(SRC)/initialize_params.c \
	 $(SRC)/draw_doors.c
OFILES = $(CFILES:.c=.o)
NAME = cub3d
SRC = ./srcs
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
