/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:52 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/11 18:42:35 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;

	input = readline(minishell->prompt); // free!
	if (!input)
		handle_error(INPUT);
	if (*input)
		add_history(input);
	return (input);
}
