/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:45:20 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/07 18:57:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *minishell)
{
	//free_lev(minishell->lev);
	//free_ast(*minishell->ast);
	//free_tokens(*minishell->token);
	deallocate_mem(minishell);
	clear_mem();
	//deallocate_mem(minishell->input);
}

int	main(int ac, char **av, char **ev)
{
	(void)av;
	if (ac != 1)
		handle_error(USAGE);
	if (!ev)
		handle_error(EV);
	start(ev);
	return (0);
}
