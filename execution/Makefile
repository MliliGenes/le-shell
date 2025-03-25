M_SRCS = main.c

M_OBJS = $(M_SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./lib/libft.a

all: $(NAME)

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(M_OBJS) $(LIBFT) -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(M_OBJS) $(B_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all