/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:07:06 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/06 18:42:41 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../lib/libft.h"

//Error Macros
#define INPUT "Error: When reading input."
#define USAGE "Usage: ./minishell"
#define ENVP "Can't allocate memory to environment variables."

//Structs
typedef struct s_data
{
	char		*input;
	const char	*prompt;
}	t_data;

#endif