/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/12 10:44:15 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_tilde(t_data *minishell, char *str)
{
	char	*home;
	char	*expanded;

	expanded = NULL;
	if (!str || str[0] != '~')
		return (str);
	home = get_key_value(*minishell->lev, "HOME");
	if (!home)
		return (str);
	if (str[1] == '\0')
		expanded = ft_strdup(home);
	else if (str[1] == '/')
		expanded = ft_strjoin(home, str + 1);
	else
		return (str);
	deallocate_mem(str);
	return (expanded);
}

static char	*handle_dollar_special_cases(t_data *minishell, char c, int *i)
{
	(*i)++;
	if (c == '?')
		return (ft_itoa(minishell->status));
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
	if (*curr == '?')
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
	char	**args;
	char	**split;
	char	*expanded;
	int		i;
	int		j;

	args = allocate_mem(1, sizeof(char *));
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '#')
			break ;
		expanded = expand_token(minishell, tokens[i]);
		expanded = expand_tilde(minishell, expanded);
		expanded = expand_wildcards(expanded);
		split = split_tokens(expanded);
		deallocate_mem(expanded);
		j = 0;
		while (split[j])
			args = ft_arrappend(args, split[j++]);
		ft_free_arr(split);
		i++;
	}
	ft_free_arr(tokens);
	return (args);
}
