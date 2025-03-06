/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/06 18:42:06 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
void	handle_error(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

char	*get_input(t_data *minishell)
{
	char	*input;

	input = readline(minishell->prompt);
	printf("%s", input);
	// if (!input)
	// 	handle_error(INPUT);
	// if (*input)
	// 	add_history(input);
	return (input);
}

t_data	*init(int ac, char **av, char **envp)
{
	t_data	*minishell;

	(void)av;
	if (ac == 1)
		handle_error(USAGE);
	if (!envp)
		handle_error(ENVP);
	minishell = malloc(sizeof(t_data));
	minishell->prompt = "minishell$ ";
	return (minishell);
}

void	free_all(t_data *minishell)
{
	free(minishell);
}

int main(int ac, char **av, char **envp)
{
	t_data *minishell;

	minishell = init(ac, av, envp);

	while (1)
	{
		// signals
		minishell->input = get_input(minishell);
		// tokenizer
		// execute
		
	}
	free_all(minishell);
	return (0);
}
