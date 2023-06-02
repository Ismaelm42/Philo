# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:35:40 by imoro-sa          #+#    #+#              #
#    Updated: 2023/06/02 12:43:30 by imoro-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	main.c				\
		philo.c				\
		philo_parse.c		\
		philo_utils.c		\
		philo_actions.c		\

OBJT = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAKEFLAGS += --quiet

all: $(NAME)
	$(MAKE) clean

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
