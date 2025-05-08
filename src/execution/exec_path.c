/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:36:33 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 18:30:46 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(char *command, char **args, t_data *minishell)
{
	struct stat	file_stat;
	char		**envp;

	if (stat(command, &file_stat) == 0)
	{
		envp = lev_to_array(minishell);
		execve(command, args, envp);
	}
	print_error(EXECVE, -1, command, NULL);
}

int	exec_parent(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

int	exec_path(t_data *minishell, char **args)
{
	pid_t	pid;
	int		res;
	char	*command;

	res = 0;
	command = find_command(minishell, args[0], &res);
	if (!command)
		return (print_command_error(res, args[0]));
	pid = fork();
	setup_signals(pid);
	if (pid == 0)
		exec_child(command, args, minishell);
	else if (pid > 0)
		res = exec_parent(pid);
	else if (pid == -1)
		handle_error(FORK);
	deallocate_mem(command);
	return (res);
}
