CC=cc
FLAGS=-Wall -Wextra -Werror -fsanitize=thread -pthread -g
INCL=libft

SRCS=philo.c \
	 exit.c \
	 parse.c \
	 init.c \
	 utils.c \
	 threads.c \
	 setters.c \
	 getters.c

OBJS=$(SRCS:%.c=%.o)

NAME=philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCL)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
