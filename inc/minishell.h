/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/12 17:35:29 by naharumi         ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"

/* ********************************* MACROS ********************************* */

# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input"
# define EV "Error: Could not allocate memory to environment variables"
# define MALLOC "Error: When using malloc"
# define BUILTIN "Error: In Builtin function"
# define EV_NOTFOUND "Error: Could not find environment variables"
# define FORK "Error: Failed to fork process"
# define PIPE_ERR "Error: Failed to create pipe"
# define DUP_ERR "Error: Failed to duplicate file descriptor"
# define TEMP_ERR "Error: Failed to create/open temporary file"
# define SIGNAL "Error: Failed to set signal handler"

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
# define SYNTAX 12
# define DIR_CMD 13
# define INVALID_PERM 14
# define AMBIGUOUS_REDIR 15
# define FALSE 0
# define TRUE 1

# define YELLOW  "\001\033[0;33m\002"
# define RESET   "\001\033[0m\002"

/* ******************************* STRUCTS ******************************* */
typedef enum e_id
{
	NONE,
	AND,
	OR,	
	PIPE,
	PAREN_OPEN,
	PAREN_CLOSE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	ARG,
}	t_id;

typedef struct s_lev
{
	char			*key;
	char			*value;
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

typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}	t_fd_list;

typedef struct s_data
{
	char		*input;
	const char	*prompt;
	int			status;
	int			ev_num;
	int			fd_bk[2];
	int			heredoc_num;
	char		**ev;
	t_lev		**lev;
	t_token		**token;
	t_ast		**ast;
}	t_data;

/* ********************************* GLOBAL ********************************* */
extern volatile int	g_signal;

/* ******************************** FUNCTIONS ******************************* */

/* ********************************** Init ********************************** */
t_data	*init(char **ev);
void	update_exit_status(t_data *minishell, int status);
void	finish(t_data *minishell);

/* ********************************* Signals ******************************** */
void	handle_sigint(int sig);
void	handle_redo_line(int sig);
void	handle_heredoc(int sig);
void	handle_sigpipe(int sig);
void	interactive_signal(void);
void	heredoc_signal(void);
void	setup_signals(int pid);

/* *********************************** Env ********************************** */
t_lev	**init_lev(t_data *minishell);
t_lev	*new_lev(char **arr_ev);
t_lev	*findlev(t_lev *lev, char *key);
void	levadd_back(t_lev **lev, t_lev *new);
void	free_lev(t_lev **lev);
int		levdel(t_lev **lev, char *key);
int		print_lev(t_lev **lev, int ordered);
int		print_lev_ord(t_data *minishell);
char	**lev_to_array(t_data *minishell);
char	**separate_ev(char *str);

/* ********************************** Input ********************************* */
char	*get_input(t_data *minishell);
int		check_input_syntax(char *str);
int		check_empty_input(char *str);
int		check_syntax(t_data *minishell, t_token *token);

/* ******************************** Tokenizer ******************************* */
t_token	**tokenizer(char *input);
t_token	*new_token(char *value, int id);
void	append_token(t_token **tokens, t_token *new);
void	free_tokens(t_token *tokens);

/* ********************************* Parser ********************************* */
t_ast	*build_tree(t_data *minishell, t_token *tokens);
t_ast	*new_node(int id);
t_token	*search_and_or(t_token *tokens);
t_token	*search_pipe(t_token *tokens);
t_token	*search_redir(t_token *tokens);
t_token	*split_token_list(t_token *tokens, t_token *op);
t_token	*remove_outer_paren(t_token *tokens);
void	parse_heredoc(t_data *minishell, t_token *op);
void	remove_heredoc_files(t_data *minishell);
void	free_ast(t_ast *node);
int		count_args(t_token *tokens);

/* ******************************** Expansor ******************************** */
char	**expansor(t_data *minishell, char **tokens);
char	*expand_token(t_data *minishell, char *token);
char	*expand_wildcards(char *pattern);
char	*handle_dollar(t_data *minishell, char *str, int *i);
char	*unquoted_dollar(t_data *minishell, char *token,	int *i, int *start);
char	*remove_quotes(char *str);
char	*get_key_value(t_lev *lev, char *key);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_arrappend(char **arr, char *new_str);
char	**split_tokens(char *str);

/* ******************************** Execution ******************************* */
char	*find_command(t_data *minishell, char *cmd, int *res);
int		exec_path(t_data *minishell, char **args);
int		loop_tree(t_data *minishell, t_ast *ast);
int		exec_pipe(t_data *minishell, t_ast *ast);
int		exec_redir(t_data *minishell, t_ast *ast, int id);
int		execute(t_data *minishell);

/* ********************************* Builtin ******************************** */
int		cd(t_lev **lev, char **args);
int		echo(char **args);
int		env(t_lev **lev, char **args);
int		exec_exit(t_data *minishell, char **args);
int		export(t_data *minishell, char **args);
int		pwd(t_data *minishell);
int		unset(t_data *minishell, char **args);
int		is_builtin(t_data *minishell, char **args);
int		hasflag(char **args);
int		validade_identifier(char *str);

/* ********************************** Utils ********************************* */
char	*concatenate(char *s1, char *s2, char *s3);
void	close_fds(int *pipe_fd);
void	restore_fds(int *fd);

/* ********************************** Error ********************************* */
void	handle_error(char *error);
int		print_command_error(int res, char *args);
int		print_error(int error, int res_num, char *command, char *arg);

#endif