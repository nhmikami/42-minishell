/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:51:46 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/08 14:57:28 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_open_quotes(char *str)
{
	int		quotes;
	char	type;

	quotes = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			type = *str;
			quotes++;
			str++;
			while (*str && *str != type)
				str++;
			if (*str == type)
				quotes++;
		}
		if (*str)
			str++;
	}
	if (quotes % 2 != 0)
		return (0);
	return (1);
}

static int	check_open_syntax(char *str)
{
	int		paren;
	char	quote;

	paren = 0;
	quote = '\0';
	if (!check_open_quotes(str))
		return (0);
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = '\0';
		else if (!quote && *str == '(')
			paren++;
		else if (!quote && *str == ')')
		{
			paren--;
			if (paren < 0)
				return (0);
		}
		str++;
	}
	return (paren == 0);
}

static int	check_special_chars(char *str)
{
	char	quote;

	quote = '\0';
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = '\0';
		else if (!quote && (*str == '\\' || *str == ';'))
			return (0);
		str++;
	}
	return (1);
}

int	check_empty_input(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_input_syntax(char *str)
{
	if (!check_open_syntax(str) || !check_special_chars(str))
		return (print_error(SYNTAX, 2, NULL, NULL));
	return (0);
}
