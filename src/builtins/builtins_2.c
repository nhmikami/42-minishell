/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:58:46 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/14 15:59:18 by cayamash         ###   ########.fr       */
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

int	exec_export(t_lev **lev, char **args)
{
	t_lev	*node;
	char	**key_value;

	if (!args[1])
		return (print_lev(lev));
	if (!validade_identifier(args[1]))
		handle_error(EXPORT_IDENTIFIER);
	key_value = ft_split(args[1], '=');
	node = ft_findlev(*lev, key_value[0]);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	else
	{
		node = ft_levnew(key_value);
		ft_levadd_back(lev, node);
	}
	return (0);
}

// int	exec_unset(char **args)
// {
// 	//só aceita o nome da variavel 
// 	//verificar se pode deletar antes
// 	return (0);
// }

int	exec_env(t_lev **lev, char **args)
{
	if (args[1])
		handle_error(ENV_ARG);
	return (print_lev(lev));
}

void exec_exit(t_data *minishell)
{
	free_all(minishell);
	exit(EXIT_SUCCESS);
}