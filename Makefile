# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 12:35:36 by adcarnec          #+#    #+#              #
#    Updated: 2023/05/09 11:19:44 by jde-la-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3
SRC			=	./src/parse/ft_init.c ./src/parse/ft_parse.c ./src/parse/ft_checkmap.c\
				./src/parse/ft_checkwall.c \
				./src/utils/ft_str.c ./src/utils/ft_tab.c ./src/utils/ft_split.c \
				./src/free/ft_free.c ./src/main.c ./src/raycasting/draw.c \
				./src/raycasting/init_rc.c ./src/utils/ft_putstr_fd.c ./src/key.c \
				./src/raycasting/minimap.c
OBJ			=	$(SRC:.c=.o)
INC_PATH	=	./inc/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I$(INC_PATH) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I$(INC_PATH) -Imlx_linux -O3 -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
