/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/02/24 20:06:11 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *input;

    (void)ac;
    (void)av;
    while (1)
    {
        // signals
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        // tokenizer
        // execute
        
        free(input);
    }
    return (0);
}
