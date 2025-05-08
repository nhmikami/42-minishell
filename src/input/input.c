/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:52 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/07 18:59:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;

	input = readline(minishell->prompt);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		finish(minishell);
	}
	if (*input)
	{
		add_history(input);
		if (check_input_syntax(input) == 0)
			return (input);
	}
	return (NULL);
}

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

int	check_input_syntax(char *str)
{
	if (!check_open_syntax(str) || !check_special_chars(str))
		return (print_error(SYNTAX, 2, NULL, NULL));
	return (0);
}
