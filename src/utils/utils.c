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

char	*concatenate(char *s1, char *s2, char *s3)
{
	char	*result1;
	char	*result2;

	result1 = ft_strjoin(s1, s2);
	result2 = ft_strjoin(result1, s3);
	deallocate_mem(result1);
	return (result2);
}

void	close_fds(int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
