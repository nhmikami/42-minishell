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

static void	heredoc_write(char *delimiter, int fd)
{
	char	*line;

	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line && g_signal == SIGINT)
		{
			free(line);
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
	return ;
}

static char *generate_path(t_data *minishell)
{
	char	*num;
	char	*path;

	num = ft_itoa(minishell->heredoc_num);
	path = concatenate("heredoc", num, ".txt");
	minishell->heredoc_num++;
	return (path);
}


char	*exec_heredoc(char *delimiter, t_data *minishell)
{
	char	*path;
	int		fd;

	path = generate_path(minishell);
	if (!path)
		handle_error(MALLOC);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	heredoc_signal();
	heredoc_write(delimiter, fd);
	close(fd);
	interactive_signal();
	dup2(minishell->stdin_bk, STDIN_FILENO);
	return (path);
}
