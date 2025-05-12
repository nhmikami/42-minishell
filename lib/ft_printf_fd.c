/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:21:50 by cayamash          #+#    #+#             */
/*   Updated: 2025/05/12 19:38:52 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putbase_fd(long long n, char *base, int div, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0 && div == 10)
	{
		write (fd, "-", 1);
		count ++;
		n = -n;
	}
	c = base[n % div];
	if (n >= div)
		count += ft_putbase_fd(n / div, base, div, fd);
	count += ft_putchar_fd(c, fd);
	return (count);
}

int	ft_putpointer_fd(unsigned long p, int fd)
{
	int		i;
	int		count;
	char	*base;
	char	str[17];

	i = 0;
	count = 0;
	base = "0123456789abcdef";
	if (!p || p == 0)
		return (ft_putstr_fd("(nil)", fd));
	count = ft_putstr_fd("0x", fd);
	while (p > 0)
	{
		str[i] = base[p % 16];
		p /= 16;
		i++;
	}
	count += i;
	i--;
	while (i >= 0)
		write(fd, &str[i--], 1);
	return (count);
}

int	ft_verify(char spec, va_list args, int fd)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count = ft_putchar_fd(va_arg(args, int), fd);
	else if (spec == 's')
		count = ft_putstr_fd(va_arg(args, char *), fd);
	else if (spec == 'd' || spec == 'i')
		count = ft_putbase_fd(va_arg(args, int), "0123456789", 10, fd);
	else if (spec == 'u')
		count = ft_putbase_fd(va_arg(args, unsigned int), "0123456789", 10, fd);
	else if (spec == 'x')
		count = ft_putbase_fd(va_arg(args, unsigned int),
				"0123456789abcdef", 16, fd);
	else if (spec == 'X')
		count = ft_putbase_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16, fd);
	else if (spec == 'p')
		count = ft_putpointer_fd(va_arg(args, unsigned long), fd);
	else if (spec == '%')
		count = ft_putchar_fd('%', fd);
	return (count);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_verify(str[i], args, fd);
		}
		else
			count += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
