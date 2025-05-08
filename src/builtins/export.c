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

static int	validade_identifier(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' || ft_isalpha(str[i]))
	{
		while (str[i] && str[i] != '=' && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i] == '=' || !str[i])
			return (1);
	}
	return (0);
}

static void	concat_args(char **args)
{
	int		i;
	char	*space;
	char	*full_arg;

	if (!args[1])
		return ;
	full_arg = ft_strdup(args[1]);
	i = 2;
	while (args[i])
	{
		space = ft_strdup(" ");
		full_arg = ft_strjoin_free(full_arg, space);
		full_arg = ft_strjoin_free(full_arg, args[i]);
		args[i] = NULL;
		i++;
	}
	deallocate_mem(args[1]);
	args[1] = full_arg;
	return ;
}

static void	export_node(t_data *minishell, char **key_value)
{
	t_lev	*node;

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
	return ;
}

int	export(t_data *minishell, char **args)
{
	char	**key_value;

	if (!args[1] || !args[1][0])
		return (print_lev_ord(minishell));
	concat_args(args);
	if (!validade_identifier(args[1]))
		return (print_error(INVALID_ID, 1, "export", args[1]));
	key_value = separate_ev(args[1]);
	if (key_value[1])
		export_node(minishell, key_value);
	ft_free_arr(key_value);
	return (0);
}
