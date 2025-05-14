/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:52 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/07 18:59:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;
	int		status;

	input = readline(minishell->prompt);
	if (g_signal == SIGINT)
		update_exit_status(minishell, SIGINT + 128);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		finish(minishell);
	}
	if (*input)
		add_history(input);
	status = check_input_syntax(input);
	if (status == 0)
		return (input);
	update_exit_status(minishell, status);
	return (NULL);
}
