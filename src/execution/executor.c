/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 13:36:57 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void execute(t_data *minishell)
{
	char **args;
	int res;

	args = ft_split(minishell->input, ' ');
	res = is_builtin(minishell, args);
	if (res != -1)
		update_exit_status(minishell, res);
	else
	{
		res = exec_path(minishell, args);
		update_exit_status(minishell, res);
	}
}
