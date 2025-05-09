/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:59 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 16:34:55 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hasflag(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && ft_isalpha(args[i][1]))
			return (i);
		i++;
	}
	return (0);
}

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

int	is_builtin(t_data *minishell, char **args)
{
	if (!ft_strncmp(args[0], "echo", 4))
		return (echo(args));
	if (!ft_strncmp(args[0], "cd", 2))
		return (cd(minishell->lev, args));
	if (!ft_strncmp(args[0], "pwd", 3))
		return (pwd());
	if (!ft_strncmp(args[0], "export", 6))
		return (export(minishell, args));
	if (!ft_strncmp(args[0], "unset", 5))
		return (unset(minishell, args));
	if (!ft_strncmp(args[0], "env", 3))
		return (env(minishell->lev, args));
	if (!ft_strncmp(args[0], "exit", 4))
		return (exec_exit(minishell, args));
	return (-1);
}
