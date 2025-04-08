/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/08 15:55:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_operators(t_data *minishell, t_ast *ast)
{
	int	res;

	res = 0;
	if (ast->id == AND)
	{
		if (ast->left)
			res = loop_tree(minishell, ast->left);
		if (res == 0 && ast->right)
			res = loop_tree(minishell, ast->right);
	}
	else if (ast->id == OR)
	{
		if (ast->left)
			res = loop_tree(minishell, ast->left);
		if (res != 0 && ast->right)
			res = loop_tree(minishell, ast->right);
	}
	else if (ast->id == PIPE)
		res = exec_pipe(minishell, ast);
	else if (ast->id == REDIR_OUT || ast->id == REDIR_IN || ast->id == APPEND)
		res = exec_redirs(minishell, ast, ast->id);
	else if (ast->id == HEREDOC)
		res = exec_heredoc(minishell, ast, 0);
	return (res);
}

int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	res;

	res = 0;
	if (ast == NULL)
		return (0);
	if (ast->args != NULL)
	{
		res = is_builtin(minishell, ast->args);
		if (res == -1)
			res = exec_path(minishell, ast->args);
	}
	else
		res = exec_operators(minishell, ast);
	return (res);
}

int	execute(t_data *minishell)
{
	int	res;
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (stdin_copy == -1 || stdout_copy == -1)
		handle_error(DUP_ERR);
	res = loop_tree(minishell, *minishell->ast);
	if (dup2(stdin_copy, STDIN_FILENO) == -1
		|| dup2(stdout_copy, STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	close(stdin_copy);
	close(stdout_copy);
	return (res);
}
