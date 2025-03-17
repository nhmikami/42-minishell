/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 17:47:19 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run(t_data *minishell)
{
	// t_token *tokens;

	// tokens = NULL;
	while (1)
	{
		// signals
		minishell->input = get_input(minishell);
		if (!minishell->input)
			handle_error(INPUT);
		//tokenizer(minishell->input, &tokens);
		//minishell->token = &tokens;
		execute(minishell);
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
	run(minishell);
	finish(minishell);
}
