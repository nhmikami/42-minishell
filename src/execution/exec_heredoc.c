/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:11 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 11:36:11 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_write(char *delimiter, char *path)
{
	char	*line;
	int		fd;
	
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			close(fd);
			exit (0);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	exit(0);
}

static char *heredoc_parent(int pid, char *path, t_data *minishell)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals(pid);
	//printf("status = %d\n", status);
	//printf("g_signal1 = %d\n", g_signal);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		update_exit_status(minishell, status); //salvar.. (status);
		free(path);
    	path = NULL;
	}
	return (path);
}

char	*exec_heredoc(char *delimiter, t_data *minishell)
{
	//int		fd;
	int		pid;
	char	*path;

	path = strdup("heredoc.txt"); //alterar para pasta temp
	if (!path)
		handle_error(MALLOC);
	pid = fork();
	if (pid == -1)
		handle_error(FORK);
	if (pid == 0)
	{
		heredoc_signal();
		heredoc_write(delimiter, path);
	}
	else 
		return(heredoc_parent(pid, path, minishell));
/*     if (g_signal == SIGINT)
	{
		update_exit_status(minishell, g_signal);
		free(path);
    	path = NULL;
	}
	interactive_signal(); */
	/* else
		return (heredoc_parent(pid, path, minishell)); */
	return (path);
}
