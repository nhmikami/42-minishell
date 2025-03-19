/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:54:00 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 13:59:32 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verify_cmd(char *cmd)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

char	**atribute_paths(t_data *minishell)
{
	t_lev	*path;
	char	**paths;

	path = findlev(*minishell->lev, "PATH");
	if (!path)
		handle_error(EV_NOTFOUND);
	paths = ft_split(path->value, ':');
	if (!paths)
		handle_error(EV_NOTFOUND);
	return (paths);
}

char	*find_command(t_data *minishell, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	full_path = verify_cmd(cmd);
	if (full_path)
		return (full_path);
	paths = atribute_paths(minishell);
	i = 0;
	while (paths[i])
	{
		full_path = concatenate(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			arrfree(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	arrfree(paths);
	return (NULL);
}