/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:42 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 18:16:07 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exit_status(t_data *minishell)
{
	t_lev	*new;
	char	*arr[3];

	arr[0] = "$";
	arr[1] = "0";
	arr[2] = NULL;
	new = new_lev(arr);
	levadd_back(minishell->lev, new);
	minishell->ev_num++;
}

void	update_exit_status(t_data *minishell, int status)
{
	t_lev	*node;
	char	*exit_status;
	
	node = findlev(*minishell->lev, "$");
	
	if (!node)
		handle_error(EV_NOTFOUND);
	else
	{
		deallocate_mem(node->value);
		exit_status = ft_itoa(status);
		node->value = ft_strdup(exit_status);
		deallocate_mem(exit_status);
	}
}

t_data	*init(char **ev)
{
	t_data	*minishell;

	minishell = allocate_mem(1, sizeof(t_data));
	minishell->prompt = YELLOW "minishell$ " RESET;
	minishell->ev = ev;
	minishell->lev = init_lev(minishell);
	init_exit_status(minishell);
	return (minishell);
}
