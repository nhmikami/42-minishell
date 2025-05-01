/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/30 23:25:40 by marvin           ###   ########.fr       */
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

static char	*handle_dollar_special_cases(t_data *minishell, char c, int *i)
{
	(*i)++;
	if (c == '?')
		return (ft_strdup(get_key_value(*minishell->lev, "$")));
	if (c == '$')
		return (ft_itoa(getpid()));
	return (NULL);
}

char	*handle_dollar(t_data *minishell, char *str, int *i)
{
	char	*curr;
	char	*var_name;
	char	*var_value;
	char	*expanded;
	int		len;

	curr = str + 1;
	if (*curr == '?' || *curr == '$')
		return (handle_dollar_special_cases(minishell, *curr, i));
	len = 0;
	while (curr[len] && (ft_isalnum(curr[len]) || curr[len] == '_'))
		len++;
	*i += len;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = allocate_mem(len + 1, sizeof(char));
	ft_strlcpy(var_name, curr, len + 1);
	var_value = get_key_value(*minishell->lev, var_name);
	if (!var_value)
		expanded = ft_strdup("");
	else
		expanded = ft_strdup(var_value);
	deallocate_mem(var_name);
	return (expanded);
}

char	**expansor(t_data *minishell, char **tokens)
{
	char	*expanded;
	int		i;

	i = 0;
	while (tokens[i])
	{
		expanded = expand_token(minishell, tokens[i]);
		expanded = expand_wildcards(expanded);
		expanded = remove_quotes(expanded);
		deallocate_mem(tokens[i]);
		tokens[i] = ft_strdup(expanded);
		deallocate_mem(expanded);
		i++;
	}
	return (tokens);
}
