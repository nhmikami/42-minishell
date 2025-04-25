/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:33:07 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/26 18:11:05 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	size;

	s_len = ft_strlen(s);
	if (!s)
		return (0);
	if (start > s_len)
	{
		size = 1;
		start = 0;
	}
	else if ((s_len - start) < len)
		size = s_len - start + 1;
	else
		size = len + 1;
	sub = allocate_mem(size, sizeof(char));
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, size);
	return (sub);
}
