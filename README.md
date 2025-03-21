# Minishell Project Guide

## Project Architecture Overview

For your Minishell project, splitting the work into parsing and execution is a sensible approach. This guide provides a comprehensive overview for both parts, focusing on the structures, algorithms, and workflows you'll need.

## Parsing Section (Using Shunting Yard Algorithm)

### Data Structures

```c
// Token types for lexical analysis
typedef enum e_token_type {
    TOKEN_WORD,        // Commands and arguments
    TOKEN_PIPE,        // |
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_APPEND,      // >>
    TOKEN_HEREDOC,     // <<
    TOKEN_AND,         // && (bonus)
    TOKEN_OR,          // || (bonus)
    TOKEN_LPAREN,      // ( (bonus)
    TOKEN_RPAREN,      // ) (bonus)
    TOKEN_EOF          // End of input
} t_token_type;

// Token structure
typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// AST node types
typedef enum e_node_type {
    NODE_COMMAND,      // Simple command with args
    NODE_PIPE,         // Pipe operator
    NODE_REDIR,        // Redirection
    NODE_AND,          // AND operator (bonus)
    NODE_OR,           // OR operator (bonus)
} t_node_type;

// AST node structure
typedef struct s_ast_node {
    t_node_type type;
    
    // For command nodes
    char **args;       // Command and its arguments
    
    // For redirection nodes
    int redir_type;    // <, >, >>, <<
    char *file;        // Filename or delimiter
    
    // Tree structure
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

// Environment variable structure
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Main shell structure
typedef struct s_shell {
    t_token *tokens;   // Linked list of tokens
    t_ast_node *ast;   // Abstract Syntax Tree root
    t_env *env;        // Environment variables
    int last_exit_code;    // $? value
    int signal_received;   // Global for signal handling
} t_shell;
```

### Tokenizer Process

1. **Input Reading**:
   - Use `readline()` to get user input
   - Add to history with `add_history()`

2. **Lexical Analysis (Tokenizer)**:
   - Process one character at a time
   - Handle quotes (single and double) properly
   - Recognize operators (`|`, `<`, `>`, `>>`, `<<`, etc.)
   - Expand environment variables within double quotes but not in single quotes
   - Create a linked list of tokens

3. **Shunting Yard Algorithm Implementation**:
   - Operator precedence (from highest to lowest):
     - `(`, `)`
     - Redirections (`<`, `>`, `>>`, `<<`)
     - `&&`, `||` (for bonus part)
     - `|` (pipe)
   - Convert infix notation to AST directly
   - Handle command groups and arguments appropriately

4. **Environment Variable Expansion**:
   - Expand `$VAR_NAME` into the corresponding value
   - Special handling for `$?` to expand to last exit status

### Parsing Steps

1. **Tokenization**: Convert input string to token linked list
2. **Syntax Validation**: Check for syntax errors (unclosed quotes, invalid operator sequences)
3. **AST Building**: Apply shunting yard to build the abstract syntax tree
4. **Variable Expansion**: Process environment variables in appropriate contexts

## Execution Section

### Data Structures (Additional)

```c
// Command execution context
typedef struct s_exec_context {
    int stdin_fd;          // Input file descriptor
    int stdout_fd;         // Output file descriptor
    int pipe_fds[2];       // Pipe file descriptors
    pid_t pid;             // Process ID
    char **envp;           // Environment variables array
    char *path;            // Executable path
    int exit_status;       // Command exit status
} t_exec_context;
```

### Execution Process

1. **Tree Traversal**:
   - Post-order traversal of the AST
   - Execute children before parents (especially important for pipes)

2. **Redirection Handling**:
   - Implement all required redirections (`<`, `>`, `>>`, `<<`)
   - Save and restore file descriptors properly
   - Handle heredoc (`<<`) with proper delimiter recognition

3. **Pipe Implementation**:
   - Create pipes between commands
   - Connect stdout of one process to stdin of the next
   - Properly close unused file descriptors

4. **Built-in Commands**:
   - Implement all required builtins:
     - `echo` with `-n` option
     - `cd` with relative/absolute paths
     - `pwd`, `export`, `unset`, `env`, `exit`
   - Execute builtins in the current process (no forking needed)

5. **External Commands**:
   - Search for executable in PATH
   - Use `fork()` and `execve()`
   - Handle execution errors properly

6. **Signal Handling**:
   - Handle SIGINT (Ctrl+C), SIGQUIT (Ctrl+\\), and EOF (Ctrl+D)
   - Implement different behavior for interactive mode vs. command execution

7. **Bonus Implementation**:
   - Logical operators (`&&`, `||`) execution with short-circuit evaluation
   - Wildcard expansion (`*`) for current directory

## Implementation Guide for Parser (Person 1)

1. **Reading Input**: Use readline() to get input and add_history() to maintain history.

2. **Tokenizer**: Process input character by character to create tokens. Be mindful of:
   - Quotes (both single and double)
   - Special characters and operators
   - Word splitting and argument recognition

3. **Shunting Yard Implementation**: Since you'll be using the Shunting Yard algorithm:
   - Define operator precedence carefully
   - Use stacks for operators and operands
   - Build tree nodes as you pop operators

4. **Environment Variable Expansion**: Expand variables:
   - Only in appropriate contexts (not in single quotes)
   - Store current exit status for $? expansion
   - Handle variable names properly (alphanumeric + underscore)

5. **AST Construction**: Build a binary tree where:
   - Internal nodes are operators (pipe, redirections, etc.)
   - Leaf nodes are commands with arguments
   - The tree structure reflects execution precedence

## Implementation Guide for Executor (Person 2)

1. **Tree Traversal**: Implement post-order traversal of the AST to execute commands.

2. **Executing Commands**:
   - Distinguish between builtins and external commands
   - For builtins: implement in the shell process
   - For external commands: fork and execve

3. **Redirection Handling**:
   - Save original file descriptors
   - Apply redirections as specified
   - Restore original file descriptors after command execution

4. **Pipe Implementation**:
   - Create pipes between commands using pipe()
   - Connect output of one command to input of the next
   - Close unused file descriptors

5. **Signal Handling**:
   - Set up signal handlers for SIGINT, SIGQUIT
   - Implement different behavior for interactive mode vs command execution

6. **Error Handling**:
   - Check return values of system calls
   - Set appropriate exit statuses
   - Print error messages with perror() or custom errors

## Integration Strategy

1. Create a shared header with all structure definitions.
2. Define clear interfaces between parsing and execution modules.
3. Use a common shell structure to pass data between components.
4. Agree on AST format and traversal method before implementation.
5. Implement incremental features - start with simple commands, then add complexity.

## Testing Strategy

1. Test parser with various inputs, including edge cases.
2. Test executor with simple commands first, then add pipes and redirections.
3. Use valgrind to check for memory leaks.
4. Compare behavior with bash for any unclear cases.

## Project Timeline Suggestion

1. Week 1: Basic structures and tokenizer
2. Week 2: Parsing and AST building
3. Week 3: Simple command execution and builtins
4. Week 4: Pipes, redirections, and signal handling
5. Week 5: Integration, testing, and debugging
6. Week 6: Bonus features and final polishing

This guide should give you a solid foundation for implementing your Minishell project. Remember to communicate regularly with your partner to ensure the parsing and execution parts integrate smoothly.