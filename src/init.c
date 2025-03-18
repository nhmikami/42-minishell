/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:42 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 17:58:45 by cayamash         ###   ########.fr       */
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
