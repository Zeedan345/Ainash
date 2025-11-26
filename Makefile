NAME = ainash
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lcurl -ljson-c

SRCS = cell.c builtin.c utils.c gemini.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
