/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:31 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 19:21:25 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_lev **lev, char **args)
{
	int flag;

	if (args[1])
	{
		if ((flag = hasflag(args)))
			print_error(INVALID_OPTION, 125, "env", args[flag]);
		else
			print_error(INVALID_ARG, 127, "env", args[1]);
	}
	return (print_lev(lev, 0));
}
