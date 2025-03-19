/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:36:33 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 14:21:36 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_sh(char *command, char **args, t_data *minishell)
{
	int			fd;
	char		buf[2];
	char		*new_args[3] = {"/bin/bash", command, NULL};

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
}

void	exec_child(char *command, char **args, t_data *minishell)
{
	struct stat	file_stat;
	int			len;

	len = ft_strlen(command);
	if (stat(command, &file_stat) == 0)
	{
		if (len > 3 && ft_strncmp(command + len - 3, ".sh", 3) == 0)
			exec_sh(command, args, minishell);
		else
			execve(command, args, lev_to_array(minishell));
	}
	print_error(EXECVE, 0, command, NULL);
}

int	exec_father(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (!(*status & 0x7F))	  // Verifica se o filho terminou normalmente (sem sinal)
		return (*status >> 8) & 0xFF; //retorna o exit status que o filho terminou
	else							 // Processo terminou por um sinal
		return 128 + (*status & 0x7F); // Obtém o número do sinal;
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
		exec_child(command, args, minishell);
	else if (pid > 0)
		res = exec_father(pid, &status);
	else
		handle_error(FORK);
	free(command);
	return (res);
}