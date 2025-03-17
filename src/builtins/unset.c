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
	if (ft_isalpha(args[1][0]) && args[1][0] != '_')
		levdel(minishell->lev, args[1]);
	minishell->ev_num--;
	return (0);
}
