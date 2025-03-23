CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = -lreadline

TARGET = parser

LIB_DIR = lib

SRC_FILES = parser.c \
	$(LIB_DIR)/string_utils_1.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(TARGET)

${TARGET}: ${OBJ_FILES}
	$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${TARGET}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(TARGET)

re: fclean all
