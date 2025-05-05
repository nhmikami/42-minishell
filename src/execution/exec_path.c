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

/* void	exec_sh(char *command, char **args, t_data *minishell)
{
	int			fd;
	char		buf[2];
	char		*new_args[3];

	new_args[0] = "/bin/bash";
	new_args[1] = command;
	new_args[2] = NULL;
	fd = open(command, O_RDONLY);
	if (fd != -1)
	{
		if (read(fd, buf, 2) == 2 && buf[0] == '#' && buf[1] == '!')
		{
			close(fd);
			execve(command, args, lev_to_array(minishell));
		}
		close(fd);
	}
	execve("/bin/bash", new_args, lev_to_array(minishell));
} */

void	exec_child(char *command, char **args, t_data *minishell)
{
	struct stat	file_stat;
	//int			len;
	char		**envp;

	//len = ft_strlen(command);
	if (stat(command, &file_stat) == 0)
	{
		/* if (len > 3 && ft_strncmp(command + len - 3, ".sh", 3) == 0)
			exec_sh(command, args, minishell);
		else
		{ */
        envp = lev_to_array(minishell);
        execve(command, args, envp);
		//}
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

int	exec_path(t_data *minishell, char **args, int is_pipe)
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
	{
		clear_fd_list(minishell);
		// ft_printf_fd(2, "filho comando - %d\n", getpid());
		exec_child(command, args, minishell);
	}
	else if (pid > 0 && !is_pipe)
		res = exec_parent(pid);
	else if (pid == -1)
		handle_error(FORK);
	deallocate_mem(command);

	if (is_pipe)
		return (pid);
	return (res);
}
