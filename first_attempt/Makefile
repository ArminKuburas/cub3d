# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 15:56:21 by akovalev          #+#    #+#              #
#    Updated: 2024/08/13 01:31:37 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wunreachable-code -Ofast #-Wall -Wextra -Werror 
LIBMLX	:= ./other_libraries/MLX42

HEADERS	:= -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -pthread -lm -L/Users/$(USER)/.brew/Cellar/glfw/3.3.8/lib -lglfw

#SRCS	:=	ray_tracing_test_01.c
SRCS	:=	./source_files/parsing/akovalev_parsing.c ./source_files/main.c ./source_files/initiate_mlx.c
#SRCS	:=	image_to_screen_test.c
			
OBJS	:= ${SRCS:.c=.o} ./other_libraries/libft/libft.a

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libmlx
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