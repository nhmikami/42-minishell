/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:17:53 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 16:17:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd("", STDOUT_FILENO);
	g_signal = SIGINT;
}

void	handle_redo_line(int sig __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc(int sig __attribute__((unused)))
{
	// printf("received SIGINT\n");
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
	g_signal = SIGINT;
	// exit(1);
}

void	heredoc_signal(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	interactive_signal(void)
{
	signal(SIGINT, handle_redo_line);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals(int pid)
{
	//struct sigaction sa;

	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
}

/* void	restore_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
} */
