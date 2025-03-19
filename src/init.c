/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:42 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 16:34:54 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exit_status(t_data *minishell)
{
	t_lev	*new;
	char	*arr[2];

	arr[0] = "$";
	arr[1] = "0";
	new = levnew(arr);
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
		free(node->value);
		exit_status = ft_itoa(status);
		node->value = ft_strdup(exit_status);
	}
}

t_data	*init(char **ev)
{
	t_data	*minishell;

	minishell = malloc(sizeof(t_data));
	minishell->prompt = "minishell$ ";
	minishell->ev = ev;
	minishell->lev = init_lev(minishell);
	init_exit_status(minishell);
	return (minishell);
}
