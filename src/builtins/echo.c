/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:34:04 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/04 18:49:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//falta colocar  lidar com " e ' + expansão de variável

int	echo(char **args) 
{
	int	i;
	int	newline;
	int	flag;

	i = 1;
	newline = 1;
	flag = hasflag(args);
	if (!ft_strncmp(args[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	else if (flag)
		return (print_error(INVALID_OPTION, 1, "echo", args[flag]));
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
