/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/30 11:01:45 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

void	update_exit_status(t_data *minishell, int status)
{
	minishell->status = status;
	g_signal = 0;
}

void	start_iteration(t_data *minishell)
{
	interactive_signal();
	if (minishell->input)
		free(minishell->input);
	remove_heredoc_files(minishell);
}

static void	run(t_data *minishell)
{
	t_ast	*root;

	while (42)
	{
		start_iteration(minishell);
		minishell->input = get_input(minishell);
		if (minishell->input != NULL && !check_empty_input(minishell->input))
		{
			minishell->token = tokenizer(minishell->input);
			if (check_syntax(minishell, *minishell->token) == 0)
			{
				root = build_tree(minishell, *minishell->token);
				if (!root)
					handle_error(MALLOC);
				minishell->ast = &root;
				if (g_signal == SIGINT)
					update_exit_status(minishell, SIGINT + 128);
				update_exit_status(minishell, execute(minishell));
				free_ast(root);
				minishell->ast = NULL;
			}
		}
	}
}

void	finish(t_data *minishell)
{
	int	exit_status;

	if (g_signal == SIGINT)
		exit_status = 130;
	else
		exit_status = minishell->status;
	close_fds(minishell->fd_bk);
	clear_mem();
	exit(exit_status);
}

int	main(int ac, char **av, char **ev)
{
	t_data	*minishell;

	(void)av;
	if (ac != 1)
		handle_error(USAGE);
	if (!ev)
		handle_error(EV);
	minishell = init(ev);
	run(minishell);
	finish(minishell);
	return (0);
}
