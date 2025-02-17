NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -rf

SRC = main.c creat_threads.c dead_monitor.c utils.c routine.c actions.c init.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

.SECONDARY: