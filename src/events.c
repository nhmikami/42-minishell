/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/11 16:11:40 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *minishell)
{
	while (1)
	{
		// signals
	
		if (minishell->input = get_input(minishell))
			minishell->token = tokenizer(minishell->input); //tokenizer
		// execute
	}
}

void	finish(t_data *minishell)
{
	free_all(minishell);
	exit(EXIT_SUCCESS);
}

void	start(char **ev)
{
	t_data *minishell;

	minishell = init(ev); // copiar env
	execute(minishell);
	finish(minishell);
}
