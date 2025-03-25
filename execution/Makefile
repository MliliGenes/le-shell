M_SRCS = main.c
M_OBJS = $(M_SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./readline-8.2 -DREADLINE_LIBRARY
LDFLAGS = -L./readline-8.2 -lreadline -lhistory -lncurses

LIBFT = ./lib/libft.a
READLINE = ./readline-8.2/libreadline.a
HISTORY = ./readline-8.2/libhistory.a

all: $(NAME)

$(NAME): $(M_OBJS) $(LIBFT) $(READLINE) $(HISTORY)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(M_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re