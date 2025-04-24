/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:45:46 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/02 16:07:19 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		deallocate_mem(arr[i]);
		i++;
	}
	deallocate_mem(arr);
	return (NULL);
}
