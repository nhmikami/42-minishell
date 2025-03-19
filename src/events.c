/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 16:34:40 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run(t_data *minishell)
{
	int	status;

	while (1)
	{
		// signals
		minishell->input = get_input(minishell);
		if (!minishell->input)
			handle_error(INPUT);
		status = verify_input(minishell->input);
		if (status == 0)
		{
			//tokenizer(minishell->input, &tokens);
			//minishell->token = &tokens;
			status = execute(minishell);
		}
		update_exit_status(minishell, status);
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
