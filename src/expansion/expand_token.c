/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/30 22:33:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_single_quotes(char *token, int *i)
{
	(*i)++;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	return ;
}

static char	*expand_double_quotes(t_data *minishell, char *token,
		int *i, int *start)
{
	char	*aux;
	char	*var;
	char	*expanded;

	expanded = ft_strdup("");
	(*i)++;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
		{
			aux = ft_substr(token, *start, *i - *start);
			var = handle_dollar(minishell, &token[*i], i);
			expanded = ft_strjoin_free(expanded, aux);
			expanded = ft_strjoin_free(expanded, var);
			*start = *i + 1;
		}
		(*i)++;
	}
	return (expanded);
}

static char	*expand_unquoted_dollar(t_data *minishell, char *token,
		int *i, int *start)
{
	char	*aux;
	char	*var;
	char	*expanded;

	expanded = ft_strdup("");
	aux = ft_substr(token, *start, *i - *start);
	var = handle_dollar(minishell, &token[*i], i);
	expanded = ft_strjoin_free(expanded, aux);
	expanded = ft_strjoin_free(expanded, var);
	*start = *i + 1;
	return (expanded);
}

char	*expand_token(t_data *minishell, char *token)
{
	int		i;
	int		start;
	char	*expanded;
	char	*aux;

	i = 0;
	start = 0;
	expanded = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '\'')
			skip_single_quotes(token, &i);
		else if (token[i] == '\"')
			expanded = ft_strjoin_free(expanded,
					expand_double_quotes(minishell, token, &i, &start));
		else if (token[i] == '$')
			expanded = ft_strjoin_free(expanded,
					expand_unquoted_dollar(minishell, token, &i, &start));
		if (token[i])
			i++;
	}
	aux = ft_substr(token, start, i - start);
	expanded = ft_strjoin_free(expanded, aux);
	return (expanded);
}
