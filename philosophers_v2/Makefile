CC=cc
CLANG=clang
FLAGS=-Wall -Wextra -Werror -pthread -g
CLANGFLAGS=-Wall -Wextra -Werror -pthread -g -fsanitize=thread

SRCS=philo.c \
	 parse.c \
	 exit.c \
	 debug.c \
	 time.c \
	 utils.c \
	 init.c \
	 threads.c

OBJS=$(SRCS:%.c=%.o)

NAME=philo

all: $(NAME)

debug: $(OBJS)
	$(CLANG) $(CLANGFLAGS) $(OBJS) -o $(NAME)
	
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
