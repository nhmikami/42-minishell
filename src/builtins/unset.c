/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:11 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 17:39:10 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_data *minishell, char **args)
{
	int	i;

	i = 1;
	while (args[i] && args[i][0])
	{
		if (validade_identifier(args[i]))
		{
			if (levdel(minishell->lev, args[i]) == 0)
				minishell->ev_num--;
		}
		i++;
	}
	return (0);
}
