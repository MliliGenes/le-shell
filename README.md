# Minishell Project Guide (Updated)

## Project Architecture Overview

### Core Components:
1. **Lexical Analysis** - Tokenize input string
2. **Syntax Parsing** - Build command structures
3. **Execution** - Run commands with proper piping/redirection

## Parsing Section

### Data Structures (from your header)

```c
// Key structures already defined in your header:
// - t_lexer: Handles input processing state
// - t_token: Token linked list with type/value
// - t_cmd: Command with args and redirections  
// - t_ast: Abstract syntax tree nodes
// - t_shell: Main shell state container
```

### Updated Parsing Workflow

1. **Lexical Analysis**:
```c
t_token *tokenize_input(t_lexer *lexer)
{
    // Implement using your t_lexer structure
    // Return linked list of t_token
}
```

2. **Command Grouping**:
```c
t_ready_token *group_tokens(t_token *tokens)
{
    // Convert token stream to command/operator sequence
    // Uses your t_ready_token structure
}
```

3. **AST Construction**:
```c
t_ast *build_ast(t_ready_token *ready_tokens)
{
    // Implement using shunting yard algorithm
    // Returns root of AST using your t_ast structure
}
```

## Execution Section

### Execution Flow

1. **AST Traversal**:
```c
int execute_ast(t_ast *node, t_shell *shell)
{
    // Recursive execution based on node type
    // Handles pipes, redirections, and logical operators
}
```

2. **Command Execution**:
```c
int execute_command(t_cmd *cmd, t_shell *shell)
{
    // Handle redirections (using your t_redir list)
    // Execute builtins or external commands
    // Manage file descriptors
}
```

3. **Redirection Handling**:
```c
void setup_redirections(t_redir *redirs)
{
    // Process each redirection in the list
    // Uses your t_redir_type enum
}
```

## Implementation Guide

### For Parser Developer:

1. **Lexer Implementation**:
   - Complete `t_lexer` functions to handle:
     - Quote handling (single/double)
     - Operator recognition
     - Word splitting

2. **Token Processing**:
   - Implement `group_tokens()` to create command/operator sequence
   - Handle operator precedence according to:
     ```
     1. Parentheses
     2. Redirections
     3. Logical AND/OR
     4. Pipes
     ```

3. **AST Construction**:
   - Use stack-based approach as in your `t_parser` structure
   - Build proper tree structure accounting for precedence

### For Executor Developer:

1. **Tree Execution**:
   - Implement post-order traversal of AST
   - Handle different node types (CMD, PIPE, AND_OR)

2. **Command Execution**:
   - Builtins vs external commands
   - Proper file descriptor management
   - Exit status propagation

3. **Redirection/Piping**:
   - Implement all redirection types from `t_redir_type`
   - Proper pipe chain creation
   - File descriptor cleanup

## Integration Points

1. **Shared Structures**:
   - Use your existing `t_ast`, `t_cmd`, and `t_token` structures
   - Agree on AST node format before implementation

2. **Interface Functions**:
```c
// Parser exposes:
t_ast *parse_input(char *input, t_shell *shell);

// Executor exposes: 
int execute_shell(t_shell *shell);
```

## Testing Strategy

1. **Unit Tests**:
   - Test lexer with various input patterns
   - Verify AST construction with different command combinations

2. **Integration Tests**:
   - Test full pipeline: input → tokens → AST → execution
   - Compare behavior with bash for complex cases

3. **Memory Management**:
   - Use your existing `ft_*` memory functions
   - Implement consistent cleanup routines

## Suggested Timeline

1. **Week 1**:
   - Complete lexer and basic tokenizer
   - Implement simple command grouping

2. **Week 2**:
   - Complete AST construction
   - Implement basic command execution

3. **Week 3**:
   - Add redirection support
   - Implement pipes

4. **Week 4**:
   - Add logical operators (&&, ||)
   - Implement subshell support

5. **Week 5**:
   - Complete builtin commands
   - Final integration and testing

Key advantages of this updated guide:
1. Better aligns with your existing header structure
2. More focused implementation path
3. Clearer separation of parsing/execution responsibilities
4. Maintains all the key functionality from original guide
