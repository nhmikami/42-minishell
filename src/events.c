/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 15:48:30 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *minishell)
{
	t_token *tokens;
	t_ast	*root;

	while (1)
	{
		// signals
		minishell->input = get_input(minishell); // dar free na lista linkada
		if (!minishell->input)
			handle_error(INPUT);
		tokens = tokenizer(minishell->input);
		root = parser(tokens);
		minishell->token = &tokens;
		minishell->root = &root;
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
