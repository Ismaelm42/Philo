# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:35:40 by imoro-sa          #+#    #+#              #
#    Updated: 2023/06/27 11:09:43 by imoro-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	philo.c				\
		philo_routine.c		\
		philo_status.c		\
		philo_utils.c		\
		philo_parse_utils.c	\

OBJT = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAKEFLAGS += --quiet

all: $(NAME)

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
