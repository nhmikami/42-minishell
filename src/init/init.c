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

t_data	*init(char **ev)
{
	t_data	*minishell;

	minishell = allocate_mem(1, sizeof(t_data));
	minishell->prompt = YELLOW "minishell$ " RESET;
	minishell->ev = ev;
	minishell->lev = init_lev(minishell);
	minishell->fd_bk[0] = -1;
	minishell->fd_bk[1] = -1;
	minishell->heredoc_num = 0;
	minishell->status = 0;
	return (minishell);
}
