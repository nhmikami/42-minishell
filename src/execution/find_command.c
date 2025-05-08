/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:54:00 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 16:35:23 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verify_cmd(char *cmd, int *res)
{
	struct stat	info;
	int			errno;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		errno = 0;
		if (access(cmd, X_OK) != 0 || stat(cmd, &info) != 0)
		{
			if (errno == EACCES)
				*res = -1;
			else if (errno == ENOENT)
				*res = -2;
			return (NULL);
		}
		if (S_ISDIR(info.st_mode))
		{
			*res = -3;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	**atribute_paths(t_data *minishell)
{
	char	*path;
	char	**paths;

	path = get_key_value(*minishell->lev, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_command(t_data *minishell, char *cmd, int *res)
{
	char	**paths;
	char	*full_path;
	int		i;

	full_path = verify_cmd(cmd, res);
	if (full_path)
		return (full_path);
	if (*res != 0)
		return (NULL);
	paths = atribute_paths(minishell);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = concatenate(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		deallocate_mem(full_path);
		i++;
	}
	ft_free_arr(paths);
	if (!paths[i])
		return (NULL);
	return (full_path);
}
