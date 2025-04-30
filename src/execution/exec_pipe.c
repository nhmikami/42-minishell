/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:26 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 11:36:26 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_child(t_data *minishell, t_ast *ast, int fd[2])
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	close(fd[1]);
	if (ast->left)
		exit(loop_tree(minishell, ast->left));
	exit(0);
}

static int	pipe_parent(t_data *minishell, t_ast *ast,
						pid_t pid, int fd[2])
{
	int		status;

    close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_error(DUP_ERR);
	close(fd[0]);
	waitpid(pid, &status, 0);
	if (ast->right)
		return (loop_tree(minishell, ast->right));
	return (0);
}

int	exec_pipe(t_data *minishell, t_ast *ast)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	handle_error(PIPE_ERR);
	pid = fork();
	if (pid == -1)
		handle_error(FORK);
	setup_signals(pid);
	if (pid == 0)
		pipe_child(minishell, ast, fd);
	else
		return (pipe_parent(minishell, ast, pid, fd));
	return (0);
}
