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

static void	heredoc_child(char *delimiter, char *path)
{
	char	*line;
	int		fd;
	
    signal(SIGINT, SIG_DFL);
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			close(fd);
			exit(0); ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	exit(0); ;
}


char	*exec_heredoc(char *delimiter)
{
	int		fd;
    int     pid;
    int     status;
    char    *path;

    path = strdup("heredoc.txt"); //alterar para pasta temp
	if (!path)
		handle_error(MALLOC);
    fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	close(fd);
    pid = fork();
	if (pid == -1)
		handle_error(FORK);
    if (pid == 0)
	    heredoc_child(delimiter, path);
    else
    {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            return(NULL);
            //salvar.. (status);
    }
	return (path);
}
