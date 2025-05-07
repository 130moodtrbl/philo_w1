# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: speters <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:07:03 by speters           #+#    #+#              #
#    Updated: 2025/05/07 15:36:27 by speters          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS =  srcs/philo.c\
		srcs/routine.c\
		srcs/simulation.c\
		srcs/state_checker.c\
		srcs/parsing.c\
		srcs/utils.c\
		srcs/forks.c\
		srcs/init.c\

OBJS = $(SRCS:.c=.o)

MAGENTA=\033[38;5;198m
RESET=\033[0m
BLUE=\033[38;5;109m

all: $(NAME)
	@echo "$(BLUE)$(NAME)\033[0m \e[0;92mdone compiling!\033[0m"
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re