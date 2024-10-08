# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 15:56:21 by akovalev          #+#    #+#              #
#    Updated: 2024/08/29 06:58:28 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wunreachable-code -Ofast -g -Wall -Wextra -Werror 
LIBMLX	:= ./other_libraries/MLX42

HEADERS	:= -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -pthread -lm -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw

SRCS	:=	./source_files/parsing/akovalev_parsing.c \
			./source_files/main.c \
			./source_files/initiate_mlx.c \
			./source_files/colour_helper_functions.c \
			./source_files/helper_functions.c \
			./source_files/player_control.c \
			./source_files/ray_calculations.c \
			./source_files/parsing/additional_parsers.c \
			./source_files/parsing/floor_ceiling_validators.c \
			./source_files/parsing/freeing_functions.c \
			./source_files/parsing/parse_directions.c \
			./source_files/parsing/island_excluder.c \
			./source_files/load_data_functions.c
			
			
OBJS	:= ${SRCS:.c=.o} ./other_libraries/libft/libft.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

./other_libraries/libft/libft.a:
	@$(MAKE) -C ./other_libraries/libft/ all

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C ./other_libraries/libft/ clean

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx