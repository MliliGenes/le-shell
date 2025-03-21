# Minishell Project

## Backlog

### Setup
- [ ] Create project structure and Makefile
- [ ] Set up Git repository
- [ ] Create initial shell loop

### Parsing (Person 1)
- [ ] Implement readline and basic input handling
- [ ] Design token structure and tokenizer functions
- [ ] Create lexical analyzer for tokenization
- [ ] Implement quote handling (single and double quotes)
- [ ] Add environment variable expansion
- [ ] Develop AST data structures
- [ ] Implement Shunting Yard algorithm for parsing
- [ ] Build AST from tokens
- [ ] Handle syntax error detection
- [ ] Implement special case for $? expansion

### Execution (Person 2)
- [ ] Create executor framework
- [ ] Implement simple command execution
- [ ] Add PATH resolution for commands
- [ ] Implement builtin commands (echo, cd, pwd)
- [ ] Implement more builtins (export, unset, env, exit)
- [ ] Add redirection handling (<, >, >>)
- [ ] Implement heredoc (<<)
- [ ] Add pipe handling
- [ ] Implement signal handling (SIGINT, SIGQUIT, EOF)
- [ ] Set up proper exit status tracking

### Integration & Testing
- [ ] Connect parser and executor
- [ ] Create basic test suite
- [ ] Add edge case tests
- [ ] Memory leak detection and fixing
- [ ] Performance optimization

### Bonus
- [ ] Implement logical operators (&&, ||)
- [ ] Add parenthesis support for priority
- [ ] Implement wildcard (*) expansion

## In Progress

## Code Review

## Done