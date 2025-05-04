NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS =  srcs/init.c\
		srcs/main.c\
		srcs/one_philo.c\
		srcs/parsing.c\
		srcs/printers.c\
		srcs/routine.c\
		srcs/sim_dinner.c\
		srcs/state_checker.c\
		srcs/utils.c\

OBJS = $(SRCS:.c=.o)

MAGENTA=\033[38;5;198m
RESET=\033[0m
BLUE=\033[38;5;109m

all: $(NAME)
	@echo "\e[1;92mcompilation ok\033[0m"
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re