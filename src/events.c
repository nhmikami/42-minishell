/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/13 19:17:50 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *minishell)
{
	t_token *tokens;

	while (1)
	{
		// signals
		minishell->input = get_input(minishell); // dar free na lista linkada
		if (!minishell->input)
			handle_error(INPUT);
		tokens = tokenizer(minishell->input);
		minishell->token = &tokens;
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
