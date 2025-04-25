/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/25 13:35:34 by marvin           ###   ########.fr       */
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

/* ********************************* Macros ********************************* */

# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input"
# define SYNTAX "Error: Invalid syntax"
# define EV "Error: Could not allocate memory to environment variables"
# define MALLOC "Error: When using malloc"
# define BUILTIN "Error: In Builtin function"
# define EV_NOTFOUND "Error: Can't find environment variables."
# define FORK "Error: Failed to fork process."
# define PIPE_ERR "Error: Failed to create pipe."
# define DUP_ERR "Error: Failed to duplicate file descriptor."
# define TEMP_ERR "Error: Failed to create/open temporary file."
# define SIGNAL "Error: Failed to set signal handler."


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
	ARG,				// todos os textos
	CMD,				// não estou usando
	FD					// não estou usando
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


/* ******************************** Functions ******************************* */

/* ********************************* Events ********************************* */
void	start(char **ev);
void	finish(void);

/* *********************************** Lev ********************************** */
t_lev	**init_lev(t_data *minishell);
t_lev	*levnew(char **arr_ev);
void	levadd_back(t_lev **lev, t_lev *new);
t_lev	*findlev(t_lev *lev, char *key);
int		levdel(t_lev **lev, char *key);
void	free_lev(t_lev **lev);
char	**lev_to_array(t_data *minishell);
int		print_lev(t_lev **lev, int ordered);
int		print_lev_ord(t_data *minishell);

/* ********************************** Init ********************************** */
t_data	*init(char **ev);
void	update_exit_status(t_data *minishell, int status);

/* ********************************** Input ********************************* */
char	*get_input(t_data *minishell);
int		verify_input(char *input);

/* ******************************** Execution ******************************* */
char	*find_command(t_data *minishell, char *cmd);
char	*exec_heredoc(char *delimiter);
int		exec_path(t_data *minishell, char **args);
int		loop_tree(t_data *minishell, t_ast *ast);
int		exec_pipe(t_data *minishell, t_ast *ast);
int		exec_redirs(t_data *minishell, t_ast *ast, int id);
int		execute(t_data *minishell);

/* ********************************* Builtin ******************************** */
int		hasflag(char **args);
int		cd(t_lev **lev, char **args);
int		echo(char **args);
int		env(t_lev **lev, char **args);
int		exec_exit(t_data *minishell, char **args);
int		export(t_data *minishell, char **args);
int		pwd(void);
int		unset(t_data *minishell, char **args);
int		is_builtin(t_data *minishell, char **args);

/* ******************************** Tokenizer ******************************* */
t_token *tokenizer(char *input);

/* ********************************* Parser ********************************* */
t_ast	*build_tree(t_token *tokens);
t_ast	*new_node(int id);
int		count_args(t_token *tokens);
int		check_syntax(t_token *token);

/* ******************************** Expansor ******************************** */
char	**expansor(t_data *minishell, char **tokens);

/* ********************************* Signals ******************************** */
void setup_signals(void);
void	restore_signals_child(void);

/* ********************************** Main ********************************** */
void	handle_error(char *error);
int	    print_error(int error, int res_num, char *command, char *arg);
void	free_all(t_data *minishell);

/* ********************************** Utils ********************************* */
int		arrlen(char **arr);
void	arrfree(char **arr);
char	*concatenate(char *s1, char *s2, char *s3);
void	*print_error_and_return(char *error);

#endif