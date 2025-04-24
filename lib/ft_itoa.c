/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:56:54 by naharumi          #+#    #+#             */
/*   Updated: 2025/03/26 17:54:40 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbr_len(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	putnbr(long n, char *str, int *i)
{
	if (n >= 10)
	{
		putnbr(n / 10, str, i);
		putnbr(n % 10, str, i);
	}
	else
	{
		str[*i] = n + '0';
		(*i)++;
	}
	return ;
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nbr;
	size_t	len;

	nbr = n;
	len = nbr_len(nbr);
	str = allocate_mem(len + 1, sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		nbr = -nbr;
		i++;
	}
	putnbr(nbr, str, &i);
	return (str);
}
