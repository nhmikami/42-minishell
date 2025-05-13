/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_submodule.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:53:12 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/13 17:28:40 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_submodule(t_data *minishell, t_ast *ast)
{
	pid_t	submod_pid;
	int		status;
	
	submod_pid = fork();
	if (submod_pid == 0)
	{
		status = loop_tree(minishell, ast);
		close_fds(minishell->fd_bk);
		clear_mem();
		exit(status);
	}
	else
	{
		waitpid(submod_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
	return (0);
}
