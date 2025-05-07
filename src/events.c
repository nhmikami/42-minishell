/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:28:39 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/07 14:45:08 by cayamash         ###   ########.fr       */
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
		g_signal = 0;
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
				if (g_signal == 0)
					status = execute(minishell);
				else
					status = SIGINT + 128;
				free_ast(root);
				minishell->ast = NULL;
			}
		}
		free(minishell->input);
		//printf("update status %d\n", status);
		update_exit_status(minishell, status);
	}
}

void	finish(void)
{
    clear_mem();
	//free_all(minishell);
	exit(EXIT_SUCCESS); //exit status
}

void	start(char **ev)
{
	t_data	*minishell;

	minishell = init(ev);
	run(minishell);
	finish();
}
