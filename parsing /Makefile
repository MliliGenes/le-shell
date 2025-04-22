CC = cc
CFLAGS = #-fsanitize=address -g -Wall -Wextra -Werror 
LIB = #-lreadline

TARGET = parser

LIB_DIR = lib
TOKENIZER_DIR = tokenizer
PROCESSING_DIR = processing
PARSING_DIR = parsing
INCLUDE_DIR = include

SRC_FILES = parser.c \
	$(LIB_DIR)/string_utils_1.c \
	$(LIB_DIR)/printing_tools.c \
	$(TOKENIZER_DIR)/token_classification.c \
	$(TOKENIZER_DIR)/token_handling.c \
	$(TOKENIZER_DIR)/token_utils.c \
	$(TOKENIZER_DIR)/token_validation.c \
	$(TOKENIZER_DIR)/token_checkers.c \
	$(TOKENIZER_DIR)/tokenizer.c \
	$(PROCESSING_DIR)/command_utils.c \
	$(PROCESSING_DIR)/operator_utils.c \
	$(PROCESSING_DIR)/processing.c \
	$(PROCESSING_DIR)/processing_utils.c \
	$(PROCESSING_DIR)/ready_token_utils.c \
	$(PROCESSING_DIR)/redirection_utils.c \
	$(PARSING_DIR)/ast_construction.c \
	$(PARSING_DIR)/parser.c \
	$(PARSING_DIR)/parser_utils.c \
	$(PARSING_DIR)/shunting_yard.c

OBJ_FILES = $(SRC_FILES:.c=.o)

INC_FLAGS = -I$(INCLUDE_DIR)

all: $(TARGET)

test: all
	./parser

${TARGET}: ${OBJ_FILES}
	@$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${TARGET} 

%.o: %.c
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(TARGET)

re: fclean all
