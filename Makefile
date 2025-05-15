CC = cc
ERRORS = #-Wall -Wextra -Werror
SANITIZER = -fsanitize=address -g3
CFLAGS = $(ERRORS) -O3 $(SANITIZER)
LIB = -L/goinfre/sel-mlil/homebrew/opt/readline/lib -lreadline 

NAME = minishell

BUILD_DIR = build

LIB_DIR = lib
TOKENIZER_DIR = tokenizer
PROCESSING_DIR = processing
PARSING_DIR = parsing
INCLUDE_DIR = include 
BUILLTINS_DIR = builtins
EXECUTION_DIR = execution
EXEC_PROC_DIR = post_processing
HEREDOC_DIR = heredoc

SRC_FILES = main.c \
	signals.c \
	$(LIB_DIR)/string_utils_1.c \
	$(LIB_DIR)/string_utils_2.c \
	$(LIB_DIR)/string_utils_3.c \
	$(LIB_DIR)/string_utils_4.c \
	$(LIB_DIR)/string_utils_5.c \
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
	$(PARSING_DIR)/shunting_yard.c \
	$(BUILLTINS_DIR)/env_utils.c \
	$(BUILLTINS_DIR)/ft_cd.c \
	$(BUILLTINS_DIR)/cd_utils.c \
	$(BUILLTINS_DIR)/ft_echo.c \
	$(BUILLTINS_DIR)/ft_env.c \
	$(BUILLTINS_DIR)/ft_exit.c \
	$(BUILLTINS_DIR)/ft_export.c \
	$(BUILLTINS_DIR)/export_utils.c \
	$(BUILLTINS_DIR)/export_env.c \
	$(BUILLTINS_DIR)/ft_pwd.c \
	$(BUILLTINS_DIR)/ft_unset.c \
	$(BUILLTINS_DIR)/builtins_utils.c \
	$(EXECUTION_DIR)/env_utils.c \
	$(EXECUTION_DIR)/execute_cmd_handle.c \
	$(EXECUTION_DIR)/execute_cmd_utils.c \
	$(EXECUTION_DIR)/redirections.c \
	$(EXECUTION_DIR)/redir_utils.c \
	$(EXECUTION_DIR)/pipe.c \
	$(EXECUTION_DIR)/and_or.c \
	$(EXECUTION_DIR)/readfile.c \
	$(EXEC_PROC_DIR)/args_utils.c \
	$(EXEC_PROC_DIR)/expention_utils.c \
	$(EXEC_PROC_DIR)/expension.c \
	$(EXEC_PROC_DIR)/join_args.c \
	$(EXEC_PROC_DIR)/split_args.c \
	$(EXEC_PROC_DIR)/remove_quotes.c \
	$(EXEC_PROC_DIR)/update_cmd_node.c \
	$(EXEC_PROC_DIR)/marking_utils.c \
	$(EXEC_PROC_DIR)/entry.c \
	$(EXEC_PROC_DIR)/entry_utils.c \
	$(EXEC_PROC_DIR)/wildcard.c \
	$(EXEC_PROC_DIR)/entry_operations.c \
	$(EXEC_PROC_DIR)/expansion_wildcard.c \
	$(HEREDOC_DIR)/open_here_docs.c


OBJ_FILES = $(patsubst %.c, ${BUILD_DIR}/%.o, $(SRC_FILES))

INC_FLAGS = -I$(INCLUDE_DIR) -I/goinfre/sel-mlil/homebrew/opt/readline/include/readline

GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
RED		= \033[0;31m
RESET	= \033[0m

all: $(NAME)
	@printf "$(GREEN)✅  Cleaned terminal$(RESET)\n"
	@clear

run: re
	@printf "$(GREEN)✅  Cleaned terminal$(RESET)\n"
	@clear
	@make clean
	@printf "$(BLUE)🚀  Running minishell...$(RESET)\n"
	@./minishell

${NAME}: ${OBJ_FILES}
	@printf "$(YELLOW)🔨  Linking objects...$(RESET)\n"
	@$(CC) $(CFLAGS) ${OBJ_FILES} $(LIB) -o ${NAME}
	@printf "$(GREEN)✅  Executable $(NAME) created$(RESET)\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)🔧  Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@printf "$(RED)🧹  Cleaning object files...$(RESET)\n"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@printf "$(RED)🧹  Removing executable $(NAME)...$(RESET)\n"
	@rm -f $(NAME)

re: fclean all
	@printf "$(GREEN)♻️  Project rebuilt$(RESET)\n"

.PHONY: all clean fclean re run