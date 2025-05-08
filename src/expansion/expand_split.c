/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/07 23:16:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*aux;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	aux = allocate_mem(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == str[i])
			quote = '\0';
		else if ((str[i] == '\"' || str[i] == '\'') && quote == '\0')
			quote = str[i];
		else
			aux[j++] = str[i];
		i++;
	}
	aux[j] = '\0';
	deallocate_mem(str);
	return (aux);
}

static int	update_quote(char c, char quote)
{
	if ((c == '\'' || c == '\"') && quote == '\0')
		return (c);
	else if (c == quote)
		return (0);
	return (quote);
}

static void	append_split(char ***split, char *str, int start, int end)
{
	char	*tmp;

	if (end > start)
	{
		tmp = ft_substr(str, start, end - start);
		tmp = remove_quotes(tmp);
		*split = ft_arrappend(*split, tmp);
		deallocate_mem(tmp);
	}
}

char	**split_tokens(char *str)
{
	char	**split;
	char	quote;
	int		i;
	int		start;

	split = allocate_mem(1, sizeof(char *));
	i = 0;
	start = 0;
	quote = '\0';
	while (str[i])
	{
		quote = update_quote(str[i], quote);
		if (str[i] == ' ' && quote == '\0')
		{
			append_split(&split, str, start, i);
			while (str[i] == ' ')
				i++;
			start = i;
			continue ;
		}
		i++;
	}
	append_split(&split, str, start, i);
	return (split);
}
