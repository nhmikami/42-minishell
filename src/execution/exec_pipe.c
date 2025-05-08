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

static void	pipe_child(t_data *minishell, t_ast *ast, int fd[2], int index)
{
	int	status;

	if (dup2(fd[index], index) == -1)
		handle_error(DUP_ERR);
	close_fds(fd);
	if (ast)
	{
		status = loop_tree(minishell, ast);
		clear_mem();
	}
	exit(status);
}

static void	wait_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
}

int	exec_pipe(t_data *minishell, t_ast *ast)
{
	int		fd[2];
	int		status[2];
	pid_t	child_pid[2];

	if (pipe(fd) == -1)
		handle_error(PIPE_ERR);
	child_pid[0] = fork();
	if (child_pid[0] == -1)
		handle_error(FORK);
	setup_signals(child_pid[0]);
	if (child_pid[0] == 0)
		pipe_child(minishell, ast->left, fd, STDOUT_FILENO);
	child_pid[1] = fork();
	setup_signals(child_pid[1]);
	if (child_pid[1] == 0)
		pipe_child(minishell, ast->right, fd, STDIN_FILENO);
	close_fds(fd);
	wait_status(child_pid[0], &status[0]);
	wait_status(child_pid[1], &status[1]);
	if (status[0] == SIGINT + 128)
		return (status[0]);
	return (status[1]);
}
