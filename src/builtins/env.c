/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:31 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/20 10:59:11 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_lev **lev, char **args)
{
	int	flag;

	if (args[1])
	{
		flag = hasflag(args);
		if (flag)
			return (print_error(INVALID_OPTION, 125, "env", args[flag]));
		else
			return (print_error(INVALID_ARG, 127, "env", args[1]));
	}
	return (print_lev(lev, 0));
}
