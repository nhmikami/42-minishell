/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 19:14:13 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	res;
	int	fd[2];
	pid_t pid;

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
	{
			if (ast->id == PIPE) // Handle pipe (|) operator
		{
			if (pipe(fd) == -1)
				handle_error(PIPE_ERR);
			pid = fork();
			if (pid == -1)
				handle_error(FORK);
			if (pid == 0) // Child process
			{
				close(fd[0]); // Close read end
				dup2(fd[1], STDOUT_FILENO); // Redirect stdout to write end
				close(fd[1]);
				exit(loop_tree(minishell, ast->left)); // Execute left subtree
			}
			else // Parent process
			{
				close(fd[1]); // Close write end
				dup2(fd[0], STDIN_FILENO); // Redirect stdin to read end
				close(fd[0]);
				waitpid(pid, &res, 0); // Wait for child
				res = loop_tree(minishell, ast->right); // Execute right subtree
			}
		}
		else if (ast->id == AND) // Handle && operator
		{
			res = loop_tree(minishell, ast->left);
			if (res == 0) // Only execute right subtree if left succeeds
				res = loop_tree(minishell, ast->right);
		}
		else if (ast->id == OR) // Handle || operator
		{
			res = loop_tree(minishell, ast->left);
			if (res != 0) // Only execute right subtree if left fails
				res = loop_tree(minishell, ast->right);
		}
		// Add more cases for >, <, etc., as neededão dependendo do id do nó
	}
	res = loop_tree(minishell, ast->right);
	return (res);
}

int	execute(t_data *minishell)
{
	int	res;

	res = loop_tree(minishell, *minishell->ast);

	return (res);
}
