# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adcarnec <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 12:35:36 by adcarnec          #+#    #+#              #
#    Updated: 2022/11/25 10:18:36 by adcarnec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
SRC			=	./src/ft_init.c ./src/main.c
OBJ			=	$(SRC:.c=.o)
INC_PATH	=	./inc/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I$(INC_PATH) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -I$(INC_PATH) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
