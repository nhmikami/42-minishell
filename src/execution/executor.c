/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 16:39:51 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	res;
	int	fd[2];
	pid_t pid;

	res = 0;
	if (!ast == NULL) 
		return ;
	loopTree(ast->left);
	if (ast->args != NULL)
	{
		res = is_builtin(minishell, ast->args);
		if (res == -1)
			res = exec_path(minishell, ast->args);
	}
	else
	{
		if (pipe(fd) == -1)
			handle_error(PIPE);
		pid = fork();
		if (pid == -1)
			handle_error(FORK)
	}
	loopTree(ast->right);
	return (res);
}

int	execute(t_data *minishell)
{
	int	res;

	res = loopTree(minishell, *minishell->ast);

	return (res);
}
