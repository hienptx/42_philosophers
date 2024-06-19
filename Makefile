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

SRCS_DIR = ./srcs
OBJS_DIR = ./objs

CC = cc -pthread
CFLAGS = -Wall -Wextra -Werror
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize

LSAN = -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer -g