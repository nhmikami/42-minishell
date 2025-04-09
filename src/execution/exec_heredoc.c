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

static void	heredoc_child(char *limiter, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

int	exec_heredoc(t_data *minishell, t_ast *ast, int parent)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error(PIPE_ERR);
	pid = fork();
	if (pid == -1)
		handle_error(FORK);
	if (pid == 0)
		heredoc_child(ast->right->args[0], fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (ast->left && !parent)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				handle_error(DUP_ERR);
			close(fd[0]);
			return (loop_tree(minishell, ast->left));
		}
		return (fd[0]);
	}
	return (0);
}
