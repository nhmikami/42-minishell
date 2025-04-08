/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/02 18:21:18 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include "libft.h"

//Handle Error Macros
# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input"
# define SYNTAX "Error: Invalid syntax"
# define EV "Can't allocate memory to environment variables"
# define MALLOC "Error: When using malloc"
# define BUILTIN "Error: In Builtin function"
# define EV_NOTFOUND "Error: Can't find environment variables."
# define FORK "Error: Trying to fork process."

//Print Error Macros
# define INVALID_OPTION 1
# define INVALID_ARG 2
# define INVALID_ID 3
# define NUMERIC_ARG 4
# define EXCEED_ARG 5
# define INVALID_FILE 6
# define INVALID_PATH 7
# define INVALID_CMD 8
# define EXECVE 9
# define INVALID_INPUT 10
# define QUOTES 11

// # define ECHO_FLAG "Error: echo doesn't accept this flag."
// # define ENV_ARG "Error: env doesn't accept arguments or flags."
// # define EXPORT_IDENTIFIER "Error: not a valid identifier."
// # define UNSET_PARAM "Error: invalid parameter name."
// # define UNSET_MATCH "Error: no matches found."
// # define UNSET_DEL "Can't unset variable."
// # define EXIT_NUM "Error: exit: numeric argument required"
// # define EXIT_ARG "Error: exit: too many arguments"
// # define EXIT_FLAG "Error: exit: minishell doesn't accept flags"


/* ********************************* Structs ********************************* */
typedef enum e_id
{
	NONE,				// =0
	AND,				// &&
	OR,					// ||
	PIPE,				// |
	PAREN_OPEN,			// (
	PAREN_CLOSE,		// )
	REDIR_IN,			// <
	REDIR_OUT,			// >
	HEREDOC,			// <<
	APPEND,				// >>
	ARG,
	CMD,
	FD
}	t_id;

typedef struct s_lev
{
	char			*key;
	char			*value;
	int				exported;
	struct s_lev	*prev;
	struct s_lev	*next;
}	t_lev;

typedef struct s_token
{
	int				id;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	int				id;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	char		*input;
	const char	*prompt;
	int			ev_num;
	char		**ev;
	t_lev		**lev;
	t_token		**token;
	t_ast		**ast;
}	t_data;

//Functions

//Utils
int		arrlen(char **arr);
void	arrfree(char **arr);
char	*concatenate(char *s1, char *s2, char *s3);
//Events
void	start(char **ev);
//List Env Var
t_lev	**init_lev(t_data *minishell);
t_lev	*levnew(char **arr_ev);
void	levadd_back(t_lev **lev, t_lev *new);
t_lev	*findlev(t_lev *lev, char *key);
int		levdel(t_lev **lev, char *key);
void	free_lev(t_lev **lev);
char	**lev_to_array(t_data *minishell);
int		print_lev(t_lev **lev, int ordered);
int		print_lev_ord(t_data *minishell);
//Init
t_data	*init(char **ev);
void	update_exit_status(t_data *minishell, int status);
//Input
char	*get_input(t_data *minishell);
int		verify_input(char *input);
//Execution
char	*find_command(t_data *minishell, char *cmd);
int		exec_path(t_data *minishell, char **args);
int		execute(t_data *minishell);
//Builtin
int		hasflag(char **args);
int		cd(t_lev **lev, char **args);
int		echo(char **args);
int		env(t_lev **lev, char **args);
int		exec_exit(t_data *minishell, char **args);
int		export(t_data *minishell, char **args);
int		pwd(void);
int		unset(t_data *minishell, char **args);
int		is_builtin(t_data *minishell, char **args);

/* ******************************* Tokenizer ******************************** */
t_token *tokenizer(char *input);

/* ********************************* Parser ********************************* */
t_ast	*build_tree(t_token *tokens);
t_ast	*new_node(int id);
int		count_args(t_token *tokens);
int		check_syntax(t_token *token);

/* ******************************** Expansor ******************************** */
char	**expansor(char **tokens);
char	*expand_token(char *token);

/* ********************************** Main ********************************** */
void	handle_error(char *error);
int		print_error(int error, int res_num, char *command, char *arg);
void	free_all(t_data *minishell);

#endif