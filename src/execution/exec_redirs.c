/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:36 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 11:36:36 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_file_fd(t_ast *ast, int id)
{
	int	file_fd;

	if (id == REDIR_OUT)
		file_fd = open(ast->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (id == APPEND)
		file_fd = open(
				ast->right->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(ast->right->args[0], O_RDONLY);
	return (file_fd);
}

static int	get_std(int id)
{
	if (id == REDIR_OUT || id == APPEND)
		return (STDOUT_FILENO);
	else
		return (STDIN_FILENO);
}

int	exec_redirs(t_data *minishell, t_ast *ast, int id)
{
	int		file_fd;
	int		status;
	int		std;
	pid_t	pid;

	file_fd = get_file_fd(ast, id);
	std = get_std(id);
	if (file_fd < 0)
		return (print_error(INVALID_FILE, 2, "open", ast->right->args[0]));
	printf("redir %s\n", ast->right->args[0]);
	pid = fork();
	if (pid == -1)
		handle_error(FORK);
    setup_signals(pid);
	if (pid == 0)
	{
		if (dup2(file_fd, std) == -1)
			handle_error(DUP_ERR);
		close(file_fd);
		exit(loop_tree(minishell, ast->left, FALSE));
	}
	else
	{
		close(file_fd);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
}
