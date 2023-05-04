# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 12:35:36 by adcarnec          #+#    #+#              #
#    Updated: 2023/05/04 09:12:23 by jde-la-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
SRC			=	./src/parse/ft_init.c ./src/main.c
OBJ			=	$(SRC:.c=.o)
INC_PATH	=	./inc/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I$(INC_PATH) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -I$(INC_PATH) -Imlx_linux -O3 -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
