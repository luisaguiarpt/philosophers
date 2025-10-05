CC=cc
CLANG=clang
FLAGS=-Wall -Wextra -Werror -pthread -g
CLANGFLAGS=-Wall -Wextra -Werror -pthread -g -fsanitize=thread -O0 -fno-omit-frame-pointer
DEBUGFLAG=-DDEBUG=1

SRCS=philo.c \
	 parse.c \
	 exit.c \
	 time.c \
	 utils.c \
	 init.c \
	 threads.c \
	 getters.c \
	 setters.c \
	 printers.c

OBJS=$(SRCS:%.c=%.o)

NAME=philo

all: $(NAME)

debug: FLAGS += $(DEBUGFLAG)
debug: fclean $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

san: $(OBJS)
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
