/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/11 20:38:33 by naharumi         ###   ########.fr       */
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

//Error Macros
# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input."
# define SYNTAX "Error: Invalid syntax"
# define EV "Can't allocate memory to environment variables."

//Structs

typedef enum e_id
{
	AND,				// &&
	OR,					// ||
	PIPE,				// |
	PAREN_OPEN,			// (
	PAREN_CLOSE,		// )
	REDIR_IN,			// <
	REDIR_OUT,			// >
	HEREDOC,			// <<
	APPEND,				// >>
	ISSPACE,
	ARG,
	NONE,
	LIMITER,
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
//Tokenizer
t_token	**tokenizer(char *input);
//Main
void	handle_error(char *error);
void	free_all(t_data *minishell);

#endif