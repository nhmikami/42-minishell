# 42-minishell
This project is about creating a simple shell. Yes, our very own little bash.

## Description
Minishell is a project that aims to recreate a simplified version of the Bash shell, providing users with a functional command-line interface.
*  Tokenizer: splits the user input into meaningful units (tokens) like commands, arguments, operators and redirection symbols 
*  Parser: builds a logical command structure from the token list — in our case, an Abstract Syntax Tree (AST)
*  Execution: traverses the parsed structure, setting up input/output redirections, managing pipes between commands, and launching the appropriate built-in functions or external programs
*  Signal handling: ensures the shell remains responsive and behaves correctly in interactive mode, handling user interruptions gracefully

## Features
*  Display a prompt when waiting for a new command
*  Have a working history
*  Execute commands (using a relative or an absolute path)
*  Built-ins implemented:
    * `echo` with `-n` option
    * `cd` with a relative or absolute path
    * `pwd` with no options
    * `export` with no options
    * `unset` with no options
    * `env` with no options or arguments
    * `exit` with no options
*  Supports the pipe operator `|` to connect commands
*  Redirections:
    *  `<` redirects input
    *  `>` redirects output in truncate mode
    *  `<<` reads user's input in heredoc mode
    *  `>>` redirects output in append mode
*  Environment variables
    *  `$` followed by a variable name, expands to the environment variable's value
    *  `$?` expands to the exit status of the most recently executed command
    *  `'` (single quotes) prevent the shell from interpreting the metacharacters 
    *  `"` (double quotes) prevent the shell from interpreting the metacharacters, but allow variable expansion
    *  `*` (wildcards) expand files and directories that matches a certain pattern
*  Logical operators
    *  `&&` executes the next command only if the previous one succeeded
    *  `||` executes the next command only if the previous one failed
*  Signals in interactive mode:
    * `ctrl-C` displays a new prompt on a new line
    * `ctrl-D` exits the shell
    * `ctrl-\` does nothing
  
