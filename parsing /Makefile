CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LIB = #-lreadline

TARGET = parser

LIB_DIR = lib

SRC_FILES = parser.c \
	$(LIB_DIR)/string_utils_1.c $(LIB_DIR)/printing_tools.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(TARGET)

test: all
	./parser 

${TARGET}: ${OBJ_FILES}
	@$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${TARGET}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(TARGET)

re: fclean all
