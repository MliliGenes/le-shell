M_SRCS = 	main.c \
			builtins.c \
			utils.c \
			builtins/ft_echo.c \
			builtins/ft_exit.c \
			builtins/ft_pwd.c \
			builtins/ft_env.c \
			builtins/ft_export.c \
			builtins/ft_unset.c \
			builtins/ft_cd.c \
			wildcards.c \
			builtins/env_utils.c \

M_OBJS = $(M_SRCS:.c=.o)

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -DREADLINE_LIBRARY
LDFLAGS = -L./lib -lreadline -lhistory -lncurses
# LDFLAGS = -lreadline -lhistory # for linux

LIBFT = ./lib/libft.a
# LIBFT = ./lib/libft-linux.a  # for linux
READLINE = ./lib/libreadline.a
HISTORY = ./lib/libhistory.a

all: $(NAME)

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $(M_OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(M_OBJS)

james: all clean
	@echo "Build complete"

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re