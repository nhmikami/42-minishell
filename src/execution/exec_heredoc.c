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

static void	heredoc_child(char *limiter, char *path)
{
	char	*line;
	int		fd;
	
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd);
			return ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
	return ;
}


char	*exec_heredoc(t_data *minishell, t_ast *ast)
{
	int		fd;
	int		status;
    char    path[17];

    path = "heredoc.txt"; //alterar para pasta temp
    fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		handle_error(TEMP_ERR);
	close(fd);
	pid = fork();
	heredoc_child(ast->right->args[0], path);
	return (path);
}
