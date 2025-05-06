/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:44 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/06 18:40:02 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_operators(t_data *minishell, t_ast *ast)
{
	int	res;
	int	status;
	int	num[2];

	res = 0;
	if (ast->id == AND)
	{
		if (ast->left)
			res = loop_tree(minishell, ast->left, FALSE);
		if (res == 0 && ast->right)
			res = loop_tree(minishell, ast->right, FALSE);
	}
	else if (ast->id == OR)
	{
		if (ast->left)
			res = loop_tree(minishell, ast->left, FALSE);
		if (res != 0 && ast->right)
			res = loop_tree(minishell, ast->right, FALSE);
	}
	else if (ast->id == PIPE)
	{
		res = exec_pipe(minishell, ast);
		
		status = 0;
		num[0] = wait(&num[1]);

		while (num[0] != -1)
		{
			if (num[0] == res)
			{
				if (WIFEXITED(status))
					status = WEXITSTATUS(num[1]);
				else 
					status = (128 + WTERMSIG(num[1]));
			}
			num[0] = wait(&num[1]);
		}
		res = status;
		clear_fd_list(minishell);
	}
	else if (ast->id >= REDIR_IN && ast->id <= APPEND)
		res = exec_redir(minishell, ast, ast->id);
	return (res);
}

int	loop_tree(t_data *minishell, t_ast *ast, int is_pipe)
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
		res = is_builtin(minishell, ast->args + i);
		if (res == -1)
			res = exec_path(minishell, ast->args + i, is_pipe);
	}
	else
		res = exec_operators(minishell, ast);
	return (res);
}

int	execute(t_data *minishell)
{
	int	res;
	// int	stdin_copy;
	// int	stdout_copy;

	// stdin_copy = dup(STDIN_FILENO);
	// stdout_copy = dup(STDOUT_FILENO);
	// if (stdin_copy == -1 || stdout_copy == -1)
	// 	handle_error(DUP_ERR);
	res = loop_tree(minishell, *minishell->ast, FALSE);
	if (dup2(minishell->stdin_bk, STDIN_FILENO) == -1
		|| dup2(minishell->stdout_bk, STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	// close(stdin_copy);
	// close(stdout_copy);
	return (res);
}
