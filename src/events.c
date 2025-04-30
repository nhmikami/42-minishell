/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/30 20:16:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run(t_data *minishell)
{
	t_token *tokens;
	t_ast	*root;
	int		status;

	while (1)
	{
		interactive_signal();
		minishell->input = get_input(minishell);
		if (!minishell->input)
			handle_error(INPUT);
		status = check_input_syntax(minishell->input);
		if (status == 0 && minishell->input[0] != '\0')
		{
			tokens = tokenizer(minishell->input);
			if (!tokens)
				handle_error(MALLOC);
			minishell->token = &tokens;
            status = check_syntax(tokens);
			if (status == 0)
			{
				root = build_tree(tokens, minishell);
				if (!root)
					handle_error(MALLOC);
				minishell->ast = &root;
                //printf("g_signal2 = %d\n", g_signal);
				status = execute(minishell);
				free_ast(root);
				minishell->ast = NULL;
			}
		}
		free(minishell->input);
		update_exit_status(minishell, status);
	}
}

void	finish(void)
{
    clear_mem();
	//free_all(minishell);
	exit(EXIT_SUCCESS);
}

void	start(char **ev)
{
	t_data	*minishell;

	minishell = init(ev);
	run(minishell);
	finish();
}
