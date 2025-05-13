/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:34:04 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/09 18:28:55 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_n_flags(char **args)
{
	int i;
	int	j;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while(args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

int	echo(char **args)
{
	int	i;
	int	newline;

	i = has_n_flags(args);
	newline = 1;
	if (i > 1)
		newline = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
