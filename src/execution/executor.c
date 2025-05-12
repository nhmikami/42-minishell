/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:44 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/12 18:39:32 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_and(t_data *minishell, t_ast *ast)
{
	int	res;

	res = 0;
	if (ast->left)
		res = loop_tree(minishell, ast->left);
	if (res == 0 && ast->right)
		res = loop_tree(minishell, ast->right);
	return (res);
}

static int	exec_or(t_data *minishell, t_ast *ast)
{
	int	res;

	res = 0;
	if (ast->left)
		res = loop_tree(minishell, ast->left);
	if (res != 0 && ast->right)
		res = loop_tree(minishell, ast->right);
	return (res);
}

int	exec_operators(t_data *minishell, t_ast *ast)
{
	int	res;

	res = 0;
	if (ast->id == AND)
		res = exec_and(minishell, ast);
	else if (ast->id == OR)
		res = exec_or(minishell, ast);
	else if (ast->id == PIPE)
		res = exec_pipe(minishell, ast);
	else if (ast->id >= REDIR_IN && ast->id <= APPEND)
		res = exec_redir(minishell, ast, ast->id);
	return (res);
}

int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (ast == NULL)
		return (0);
	if (ast->args != NULL)
	{
		ast->args = expansor(minishell, ast->args);
		while (ast->args[i] && ast->args[i][0] == '\0')
			i++;
		if (!ast->args[i])
			return (0);
		res = is_builtin(minishell, &ast->args[i]);
		if (res == -1)
			res = exec_path(minishell, &ast->args[i]);
	}
	else
		res = exec_operators(minishell, ast);
	return (res);
}

int	execute(t_data *minishell)
{
	int	res;

	res = loop_tree(minishell, *minishell->ast);
	if (dup2(minishell->fd_bk[0], STDIN_FILENO) == -1
		|| dup2(minishell->fd_bk[1], STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	close_fds(minishell->fd_bk);
	restore_fds(minishell->fd_bk);
	return (res);
}
