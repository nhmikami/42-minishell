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

static void	heredoc_write(char *delimiter, char *path, int fd)
{
	char	*line;
	// int		fd;
	
	// fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line && g_signal == SIGINT)
		{
			free(line);
			//close(fd);
			return ;
		}
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	//close(fd);
	return ;
}

static char *generate_path(t_data *minishell)
{
	char	*num;
	char	*path;
	int		num_len;

	num = ft_itoa(minishell->heredoc_num);
	num_len = ft_strlen(num);
	path = concatenate("/temp/heredoc", num, ".txt");
	minishell->heredoc_num++;
	free(num);
	return (path);
}


char	*exec_heredoc(char *delimiter, t_data *minishell)
{
	char	*path;
	int		fd;

	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	path = generate_path(minishell);
	if (!path)
		handle_error(MALLOC);
	heredoc_signal();
	heredoc_write(delimiter, path, fd);
	close(fd);
	interactive_signal();
	dup2(minishell->stdin_bk, STDIN_FILENO);
	return (path);
}
