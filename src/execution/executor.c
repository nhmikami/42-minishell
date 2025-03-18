/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 18:11:52 by cayamash         ###   ########.fr       */
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

char	*find_command(t_data *minishell, char *cmd)
{
	t_lev	*path;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path = findlev(*minishell->lev, "PATH");
	if (!path)
		handle_error(EV_NOTFOUND);
	paths = ft_split(path->value, ':');
	if (!paths)
		handle_error(EV_NOTFOUND);
	i = 0;
	while (paths[i])
	{
		full_path = concatenate(paths[i], "/", cmd);
		if (access(full_path, X_OK == 0))
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

int	exec_path(t_data *minishell, char **args)
{
	pid_t	pid;
	char	*command;
	int		status;
	int		res;

	res = 0;
	command = find_command(minishell, args[0]);
	if (!command)
		return (print_error(INVALID_CMD, 127, args[0], NULL));
	pid = fork();
	if (pid == 0)
	{
		execve(command, args, lev_to_array(minishell));
		handle_error(EXECVE);//TA DANDO ESSE ERRO!
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0); //quando o comando não existe, exit status é 127, nesse caso, imprimir "comando inexistente"
		if (!(status & 0x7F))  // Verifica se o filho terminou normalmente (sem sinal)
			res = (status >> 8) & 0xFF;
		else // Processo terminou por um sinal
			res = 128 + (status & 0x7F);  // Obtém o número do sinal;
	}
	else
		handle_error(FORK);
	free(command);
	return (res);
}

void	execute(t_data *minishell)
{
	char	**args;
	int		res;

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

