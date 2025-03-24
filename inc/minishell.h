/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/20 14:27:33 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

/* ********************************* Macros ********************************** */
# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input"
# define SYNTAX "Error: Invalid syntax"
# define EV "Can't allocate memory to environment variables"
# define MALLOC "Error: Could not allocate memory"

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
	t_lev		**lev;
	t_token		**token;
	t_ast		**root;
}	t_data;

//Functions
//Utils
int		ft_arrlen(char **arr);
void	ft_arrfree(char **arr);
//Events
void	start(char **ev);
//Init
t_data	*init(char **ev);
//Input
char	*get_input(t_data *minishell);

/* ******************************* Tokenizer ******************************** */
t_token *tokenizer(char *input);

/* ********************************* Parser ********************************* */
t_ast	*parser(t_token *tokens);
t_ast	*parse_group(t_token **tokens);
t_ast	*parse_and_or(t_token **tokens);
t_ast	*parse_pipe(t_token **tokens);
t_ast	*parse_redir(t_token **tokens);
t_ast	*parse_token(t_token **tokens);
t_ast	*new_node(int id);
int		count_args(t_token *tokens);

/* ********************************** Main ********************************** */
void	handle_error(char *error);
void	free_all(t_data *minishell);

#endif