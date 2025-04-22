CC = cc
CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror 
LIB = #-lreadline

TARGET = le-shell

LIB_DIR = lib
TOKENIZER_DIR = tokenizer
PROCESSING_DIR = processing

SRC_FILES = parser.c \
	$(LIB_DIR)/string_utils_1.c $(LIB_DIR)/printing_tools.c \
	$(TOKENIZER_DIR)/tokenizer.c \
	$(PROCESSING_DIR)/processing.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(TARGET)

test: all
	./le-shell

${TARGET}: ${OBJ_FILES}
	@$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${TARGET} 

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(TARGET)

re: fclean all
