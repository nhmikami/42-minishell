/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:36:33 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 16:31:07 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_export(t_data *minishell, char *arg)
{
	t_lev	*node;
	char	**key_value;

	key_value = separate_ev(arg);
	node = findlev(*minishell->lev, key_value[0]);
	if (node)
	{
		deallocate_mem(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	else
	{
		node = new_lev(key_value);
		levadd_back(minishell->lev, node);
		minishell->ev_num++;
	}
	ft_free_arr(key_value);
}

int	export(t_data *minishell, char **args)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	if (!args[i])
		return (print_lev_ord(minishell));
	if (args[1] && args[1][0] == 0)
		return (print_error(INVALID_ID, 1, "export", args[1]));
	while (args[i] && args[i][0])
	{
		if (!validade_identifier(args[i]))
			res = print_error(INVALID_ID, 1, "export", args[i]);
		else
			exec_export(minishell, args[i]);
		i++;
	}
	return (res);
}
