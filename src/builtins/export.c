/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:36:33 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 11:07:55 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validade_identifier(char *str)
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

int	export(t_data *minishell, char **args)
{
	t_lev	*node;
	char	**key_value;

	if (!args[1] || !args[1][0])
		return (print_lev_ord(minishell));
	if (!validade_identifier(args[1]))
		print_error(INVALID_ID, 1, "export", args[1]);
	key_value = ft_split(args[1], '=');
	node = findlev(*minishell->lev, key_value[0]);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	else
	{
		node = levnew(key_value);
		levadd_back(minishell->lev, node);
		minishell->ev_num++;
	}
	return (0);
}
