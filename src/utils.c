/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:50:33 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 15:38:55 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	arrfree(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		deallocate_mem(arr[i]);
		i++;
	}
	deallocate_mem(arr);
}

char	*concatenate(char *s1, char *s2, char *s3)
{
	char	*result1;
	char	*result2;

	result1 = ft_strjoin(s1, s2);
	result2 = ft_strjoin(result1, s3);
	deallocate_mem(result1);
	return (result2);
}
