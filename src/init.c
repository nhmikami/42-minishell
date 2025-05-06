/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:42 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 18:16:07 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(t_data *minishell, int status)
{
	minishell->status = status;
}

t_data	*init(char **ev)
{
	t_data	*minishell;

	minishell = allocate_mem(1, sizeof(t_data));
	minishell->prompt = YELLOW "minishell$ " RESET;
	minishell->ev = ev;
	minishell->lev = init_lev(minishell);
	minishell->stdin_bk = dup(STDIN_FILENO);
	minishell->stdout_bk = dup(STDOUT_FILENO);
	if (minishell->stdin_bk == -1 || minishell->stdout_bk == -1)
		handle_error(DUP_ERR);
	minishell->heredoc_num = 0;
	minishell->fd_list = NULL; //tirar quando pipe der fork
	minishell->status = 0;
	return (minishell);
}
