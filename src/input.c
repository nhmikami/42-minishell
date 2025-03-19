/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:52 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 16:32:24 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;

	input = readline(minishell->prompt);
	if (!input)
		handle_error(INPUT);
	if (*input)
		add_history(input);
	return (input);
}

int	verify_input(char *input)
{
	if (ft_strchr(input, '\\'))
	{
		print_error(INVALID_INPUT, 1, "\\ (backslash)", NULL);
		return (1);
	}
	if (ft_strchr(input, ';'))
	{
		print_error(INVALID_INPUT, 1, "; (semicolon)", NULL);
		return (2);
	}
	return (0);
}
