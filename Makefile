# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 16:32:40 by hipham            #+#    #+#              #
#    Updated: 2024/06/19 18:30:06 by hipham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -lpthread
CFLAGS = -Wall -Wextra -Werror -I./includes
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize

LSAN = -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer -g

SRCS = philo.c args_handlind.c
OBJS = (SRCS:%.o=%.c)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LSAN) -o $a $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
