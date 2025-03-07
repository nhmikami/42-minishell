/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/07 18:28:29 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *minishell)
{
	while (1)
	{
		// signals
		minishell->input = get_input(minishell);
		// tokenizer
		// execute
	}
}

void	finish(t_data *minishell)
{
	free_all(minishell);
	exit(EXIT_SUCCESS);
}

void	start(int ac, char **av, char **ev)
{
	t_data *minishell;

	minishell = init(ac, av, ev); // copiar env
	execute(minishell);
	finish(minishell);
}
