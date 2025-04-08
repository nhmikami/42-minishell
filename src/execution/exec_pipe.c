/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:00:44 by marvin            #+#    #+#             */
/*   Updated: 2025/04/08 16:00:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_child(t_data *minishell, t_ast *ast, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	close(fd[1]);
	if (ast->left && ast->left->id != HEREDOC)
		exit(loop_tree(minishell, ast->left));
	exit(0);
}

static int	pipe_parent(t_data *minishell, t_ast *ast,
						pid_t pid, int fd_out)
{
	int		status;

	if (dup2(fd_out, STDIN_FILENO) == -1)
		handle_error(DUP_ERR);
	close(fd_out);
	waitpid(pid, &status, 0);
	if (ast->right)
		return (loop_tree(minishell, ast->right));
	return (0);
}

int	exec_pipe(t_data *minishell, t_ast *ast)
{
	int		fd[2];
	int		heredoc_fd;
	pid_t	pid;

	heredoc_fd = -1;
	if (pipe(fd) == -1)
		handle_error(PIPE_ERR);
	if (ast->left && ast->left->id == HEREDOC)
		heredoc_fd = exec_heredoc(minishell, ast->left, 1);
	pid = fork();
	if (pid == -1)
		handle_error(FORK);
	if (pid == 0)
		pipe_child(minishell, ast, fd);
	else
	{
		close(fd[1]);
		if (heredoc_fd != -1)
			return (pipe_parent(minishell, ast, pid, heredoc_fd));
		else
			return (pipe_parent(minishell, ast, pid, fd[0]));
	}
	return (0);
}
