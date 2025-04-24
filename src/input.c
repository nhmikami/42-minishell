/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:52 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/24 16:35:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;

	input = readline(minishell->prompt);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		finish();
	}
	if (*input)
		add_history(input);
	return (input);
}

int	verify_input(char *input)
{
	if (ft_strchr(input, '\\'))
		return (print_error(INVALID_INPUT, 1, "\\ (backslash)", NULL));
	if (ft_strchr(input, ';'))
		return (print_error(INVALID_INPUT, 2, "; (semicolon)", NULL));
	return (0);
}
