/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:40:51 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/19 16:34:57 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *minishell)
{
	char	**args;
	int		res;

	args = ft_split(minishell->input, '_'); //args = ft_split(minishell->input, ' ');
	res = is_builtin(minishell, args);
	if (res == -1)
		res = exec_path(minishell, args);
	return (res);
}
