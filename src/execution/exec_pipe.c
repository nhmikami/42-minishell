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

	//printf("exec child %d\n", ast->id);
	if (dup2(fd[index], index) == -1)
		handle_error(DUP_ERR);
	close_pipe(fd);
	if (ast)
	{
		status = loop_tree(minishell, ast, TRUE);
		clear_mem();
	}
	exit(status);
}

static void	wait_status(pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	//printf("receive status %d from pid %d\n", *status, pid);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
	{
		if (*status == SIGINT)
			write(STDIN_FILENO, "\n", 1);
		*status = WTERMSIG(*status) + 128;
	}
}

// static int	pipe_parent(t_data *minishell, t_ast *ast,
// 						int fd[2])
// {
// 	int	status;
// 	int	num[2];
// 	int	pid;
//  close(fd[1]);
// 	if (dup2(fd[0], STDIN_FILENO) == -1)
// 		handle_error(DUP_ERR);
// 	close(fd[0]);
// 	if (ast->right)
// 		pid = loop_tree(minishell, ast->right, TRUE);
// 	status = 0;
// 	num[0] = wait(&num[1]);
// 	while (num[0] != -1)
// 	{
// 		if (num[0] == pid)
// 		{
// 			if (WIFEXITED(status))
// 				status = WEXITSTATUS(num[1]);
// 			else 
// 				status = (128 + WTERMSIG(num[1]));
// 		}
// 		num[0] = wait(&num[1]);
// 	}
// 	return (status);
// }


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
	close_pipe(fd);
	wait_status(child_pid[0], &status[0]);
	wait_status(child_pid[1], &status[1]);
	while (wait(NULL) > 0) ;
	if (status[0] == SIGINT + 128)
		return (status[0]);
	return (status[1]);
}



// int	exec_pipe(t_data *minishell, t_ast *ast)
// {
// 	int	pid;
// 	// int	status;
// 	int	fd[2];
// 	// int	num[2];
// 	int	old_fd[2];
// 	//////////////////////////////////////////
// 	pid = -1;
// 	if (ast->id == PIPE)
// 	{
// 		if (pipe(fd) == -1)
// 			handle_error(PIPE_ERR);	
// 		add_fd_list(minishell, fd[0]);
// 		add_fd_list(minishell, fd[1]);
// 		old_fd[0] = dup(STDIN_FILENO);
// 		old_fd[1] = dup(STDOUT_FILENO);
// 		add_fd_list(minishell, old_fd[0]);
// 		add_fd_list(minishell, old_fd[1]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		if (ast->left)
// 			exec_pipe(minishell, ast->left);
// 		// Comando da direita
// 		// redir_back_old_fd_out();
// 		dup2(old_fd[1], STDOUT_FILENO);
// 		close(old_fd[1]);
// 		// redir_in();
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		if (ast->right)
// 			pid = exec_pipe(minishell, ast->right);
// 		// redir_back_old_fd_in();
// 		dup2(old_fd[0], STDIN_FILENO);
// 		close(old_fd[0]);
// 	}
// 	else
// 		pid = loop_tree(minishell, ast, TRUE);
// 	return (pid);
// 	///////////////////////////////////////////////
// 	///////////////////////////////////////////////
// 	// status = 0;
// 	// num[0] = wait(&num[1]);
// 	// while (num[0] != -1)
// 	// {
// 	// 	if (num[0] == pid)
// 	// 	{
// 	// 		if (WIFEXITED(status))
// 	// 			status = WEXITSTATUS(num[1]);
// 	// 		else 
// 	// 			status = (128 + WTERMSIG(num[1]));
// 	// 	}
// 	// 	num[0] = wait(&num[1]);
// 	// }
// 	///////////////////////////////////////////////
// 	// return (status);
// }
