CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -fomit-frame-pointer #-g -fsanitize=address
LIB = -lreadline

NAME = le-shell

BUILD_DIR = build

LIB_DIR = lib
TOKENIZER_DIR = tokenizer
PROCESSING_DIR = processing
PARSING_DIR = parsing
INCLUDE_DIR = include

SRC_FILES = main.c \
	$(LIB_DIR)/string_utils_1.c \
	$(LIB_DIR)/error_utils.c \
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

OBJ_FILES = $(patsubst %.c, ${BUILD_DIR}/%.o, $(SRC_FILES))

INC_FLAGS = -I$(INCLUDE_DIR)

all: $(NAME)

run: re
	make clean
	./le-shell

${NAME}: ${OBJ_FILES}
	@$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${NAME} 

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run