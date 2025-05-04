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

// static void	pipe_child(t_data *minishell, t_ast *ast, int fd[2])
// {
// 	// close(fd[0]);
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		handle_error(DUP_ERR);
// 	close(fd[1]);
// 	if (ast->left)
// 	{
// 		loop_tree(minishell, ast->left, TRUE);
// 		// clear_mem();
// 	}
// 	// exit(0);
// }

// static int	pipe_parent(t_data *minishell, t_ast *ast,
// 						int fd[2])
// {
// 	int	status;
// 	int	num[2];
// 	int	pid;

//     // close(fd[1]);
// 	if (dup2(fd[0], STDIN_FILENO) == -1)
// 		handle_error(DUP_ERR);
// 	close(fd[0]);
// 	if (ast->right)
// 		pid = loop_tree(minishell, ast->right, TRUE);

	// status = 0;
	// num[0] = wait(&num[1]);

	// while (num[0] != -1)
	// {
	// 	if (num[0] == pid)
	// 	{
	// 		if (WIFEXITED(status))
	// 			status = WEXITSTATUS(num[1]);
	// 		else 
	// 			status = (128 + WTERMSIG(num[1]));
	// 	}
	// 	num[0] = wait(&num[1]);
	// }

// 	return (status);
// }

// int	exec_pipe(t_data *minishell, t_ast *ast)
// {
// 	int		fd[2];
// 	// pid_t	pid;

// 	// ft_printf_fd(2, "pai - %d\n", getpid());

// 	if (pipe(fd) == -1)
// 		handle_error(PIPE_ERR);
// 	// pid = fork();
// 	// if (pid == -1)
// 	// 	handle_error(FORK);
// 	// setup_signals(pid);
// 	// if (pid == 0)
// 	// {
// 		// ft_printf_fd(2, "filho pipe - %d\n", getpid());
// 		pipe_child(minishell, ast, fd);
// 	// }
// 	// else
// 		return (pipe_parent(minishell, ast, fd));
// 	return (0);
// }



int	exec_pipe(t_data *minishell, t_ast *ast)
{
	int	pid;
	// int	status;
	int	fd[2];
	// int	num[2];
	int	old_fd[2];

	//////////////////////////////////////////
	pid = -1;
	if (ast->id == PIPE)
	{
		if (pipe(fd) == -1)
			handle_error(PIPE_ERR);
		
		add_fd_list(minishell, fd[0]);
		add_fd_list(minishell, fd[1]);

		old_fd[0] = dup(STDIN_FILENO);
		old_fd[1] = dup(STDOUT_FILENO);
		add_fd_list(minishell, old_fd[0]);
		add_fd_list(minishell, old_fd[1]);

		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		if (ast->left)
			exec_pipe(minishell, ast->left);

		// Comando da direita
		// redir_back_old_fd_out();
		dup2(old_fd[1], STDOUT_FILENO);
		close(old_fd[1]);

		// redir_in();
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		if (ast->right)
			pid = exec_pipe(minishell, ast->right);

		// redir_back_old_fd_in();
		dup2(old_fd[0], STDIN_FILENO);
		close(old_fd[0]);
	}
	else
		pid = loop_tree(minishell, ast, TRUE);
	return (pid);
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// status = 0;
	// num[0] = wait(&num[1]);

	// while (num[0] != -1)
	// {
	// 	if (num[0] == pid)
	// 	{
	// 		if (WIFEXITED(status))
	// 			status = WEXITSTATUS(num[1]);
	// 		else 
	// 			status = (128 + WTERMSIG(num[1]));
	// 	}
	// 	num[0] = wait(&num[1]);
	// }
	///////////////////////////////////////////////

	// return (status);
}
