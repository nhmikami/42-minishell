/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/07 21:01:21 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_tilde(t_data *minishell, char *str)
{
	char	*home;
	char	*expanded;
	
	if (!str || str[0] != '~')
		return (ft_strdup(str));
	if (str[1] == '\0' || str[1] == '/')
	{
		home = get_key_value(*minishell->lev, "HOME");
		if (!home)
			return (ft_strdup(str));
		expanded = ft_strjoin(home, str + 1);
		return (expanded);
	}
	return (ft_strdup(str));
}

static char *remove_comments(char *str)
{
	int		i;
	int		in_quote;
	char	quote;

	i = 0;
	in_quote = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !in_quote)
		{
			quote = str[i];
			in_quote = 1;
		}
		else if (str[i] == quote && in_quote)
			in_quote = 0;
		else if (str[i] == '#' && !in_quote)
			break;
		i++;
	}
	return (ft_substr(str, 0, i));
}

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

/*char	**smart_split(char *str)
{
	char	**split;
	char	*aux;
	int		i;
	int		start;
	char	quote;

	i = 0;
	start = 0;
	quote = '\0';
	split = allocate_mem(1, sizeof(char *));
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == '\0')
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		else if (str[i] == ' ' && quote == '\0')
		{
			if (i > start)
			{
				aux = remove_quotes(ft_substr(str, start, i - start));
				split = ft_arrappend(split, aux);
				deallocate_mem(aux);
			}
			while (str[i] == ' ')
				i++;
			start = i;
			continue ;
		}
		i++;
	}
	if (i > start)
	{
		aux = remove_quotes(ft_substr(str, start, i - start));
		split = ft_arrappend(split, aux);
		deallocate_mem(aux);
	}
	return (split);
}*/

static int	update_quote(char c, char quote)
{
	if ((c == '\'' || c == '\"') && quote == '\0')
		return (c);
	else if (c == quote)
		return (0);
	return (quote);
}

static void	append_split(char **split, char *str, int start, int end)
{
	char	*tmp;

	if (end > start)
	{
		tmp = ft_substr(str, start, end - start);
		tmp = remove_quotes(tmp);
		split = ft_arrappend(split, tmp);
		deallocate_mem(tmp);
	}
}

char	**smart_split(char *str)
{
	char	**split;
	int		i;
	int		start;
	char	quote;

	split = allocate_mem(1, sizeof(char *));
	i = 0;
	start = 0;
	quote = '\0';
	while (str[i])
	{
		write(1, &str[i], 1);
		quote = update_quote(str[i], quote);
		if (str[i] == ' ' && quote == '\0')
		{
			append_split(split, str, start, i);
			while (str[i] == ' ')
				i++;
			start = i;
			continue ;
		}
		i++;
	}
	append_split(split, str, start, i);
	return (split);
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
		expanded = expand_token(minishell, tokens[i]);
		expanded = expand_tilde(minishell, expanded);
		expanded = remove_comments(expanded);
		expanded = expand_wildcards(expanded);
		printf("%s\n", expanded);
		split = smart_split(expanded);
		printf("saiu\n");
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

/*
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
*/