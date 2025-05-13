/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_submodule.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:53:12 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/13 14:32:52 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_submodule(t_data *minishell, t_ast *ast)
{
	pid_t	submod_pid;
	int		status;
	
	submod_pid = fork();
	if (submod_pid == 0)
		loop_tree(minishell, ast);
	else
	{
		waitpid(submod_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
	return (0);
}