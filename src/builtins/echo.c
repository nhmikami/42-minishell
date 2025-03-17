/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:34:04 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/17 19:12:08 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args) //colocar expansão de variável
{
	int	i;
	int	newline;
	int	flag;

	i = 1;
	newline = 1;
	if (!ft_strncmp(args[i], "-n", 2))
	{
		newline = 0;
		i++;
	}
	else if ((flag = hasflag(args)))
		print_error(INVALID_OPTION, 1, "echo", args[flag]);
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
