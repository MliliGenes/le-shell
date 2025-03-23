M_SRCS = main.c

M_OBJS = $(M_SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(M_OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(M_OBJS) ./libft/libft.a -lreadline


%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	rm -rf $(M_OBJS) $(B_OBJS)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all