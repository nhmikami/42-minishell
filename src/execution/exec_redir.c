/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:36 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 11:36:36 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_permission(t_ast *ast, int id)
{
	char	*filename;

	filename = ast->right->args[0];
	if (id == REDIR_OUT || id == APPEND)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) != 0)
			return (0);
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, R_OK) != 0)
			return (0);
	}
	return (1);
}

static int	get_file_fd(t_ast *ast, int id)
{
	int		file_fd;
	char	*filename;

	filename = ast->right->args[0];
	if (id == REDIR_OUT)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (id == APPEND)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		file_fd = open(filename, O_RDONLY);
	return (file_fd);
}

static int	get_std(int id)
{
	if (id == REDIR_OUT || id == APPEND)
		return (STDOUT_FILENO);
	else
		return (STDIN_FILENO);
}

int	exec_redir(t_data *minishell, t_ast *ast, int id)
{
	int		file_fd;
	int		std;

	//printf("redirecionando\n"); // APAGAR
	ast->right->args = expansor(minishell, ast->right->args);
	if (ast->right && ast->right->args && ast->right->args[1])
		return (print_error(AMBIGUOUS_REDIR, 1, NULL, NULL));
	if (!check_file_permission(ast, id))
		return (print_error(INVALID_PERM, 1, NULL, NULL));
	file_fd = get_file_fd(ast, id);
	if (file_fd < 0)
		return (print_error(INVALID_FILE, 1, "open", ast->right->args[0]));
	std = get_std(id);
	if (dup2(file_fd, std) == -1)
	{
		close(file_fd);
		handle_error(DUP_ERR);
	}
	close(file_fd);
	return (loop_tree(minishell, ast->left, FALSE));
}
