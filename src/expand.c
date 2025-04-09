/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:01:31 by naharumi          #+#    #+#             */
/*   Updated: 2025/04/09 15:34:26 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// utils
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	
	result = ft_strjoin(s1, s2);
	if (s1)
		deallocate_mem(s1);
	if (s2)
		deallocate_mem(s2);
	return (result);
}

char	**ft_arrappend(char **arr, char *new_str)
{
	int		i;
	int		len;
	char	**new_arr;

	len = ft_arrlen(arr);
	new_arr = allocate_mem(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i++] = ft_strdup(new_str);
	new_arr[i] = NULL;
	ft_free_arr(arr);
	return (new_arr);
}

char	*get_exit_status(t_lev *lev, char *key)
{
	t_lev	*env_var;

	env_var = findlev(lev, key);
	return (env_var->value);
}

// dollar
char	*handle_dollar(t_data *minishell, char *str, int *i)
{
	char	*curr;
	char	*var_name;
	char	*var_value;
	char	*expanded;
	int		len;

	curr = str + 1;
	if (*curr == '?' || *curr == '$')
	{
		(*i)++;
		if (*curr == '?')
			return (ft_strdup(get_exit_status(*minishell->lev), "$")));
		else if (*curr == '$')
			return (ft_itoa(getpid()));
	}
	len = 0;
	while (curr[len] && (ft_isalnum(curr[len]) || curr[len] == '_'))
		len++;
	*i += len;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = allocate_mem(len + 1, sizeof(char));
	ft_strlcpy(var_name, curr, len + 1);
	if (len == 1 && !ft_strncmp(var_name, "_", 1))
		expanded = ft_strdup(""); // implementar: expanded = get_last_argument();
	else
	{
		var_value = getenv(var_name);
		if (!var_value)
			expanded = ft_strdup("");
		else
			expanded = ft_strdup(var_value);
	}
	deallocate_mem(var_name);
	return (expanded);
}

char	*expand_token(t_data *minishell, char *token)
{
	int		i;
	int		start;
	char	*var;
	char	*aux;
	char	*expanded;

	i = 0;
	start = 0;
	expanded = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '\'')
		{
			i++;
			while (token[i] && token[i] != '\'')
				i++;
		}
		else if (token[i] == '\"')
		{
			i++;
			while (token[i] && token[i] != '\"')
			{
				if (token[i] == '$')
				{
					aux = ft_substr(token, start, i - start);
					var = handle_dollar(minishell, &token[i], &i);
					expanded = ft_strjoin_free(expanded, aux);
					expanded = ft_strjoin_free(expanded, var);
					start = i + 1;
				}
				i++;
			}
		}
		else if (token[i] == '$')
		{
			aux = ft_substr(token, start, i - start);
			var = handle_dollar(minishell, &token[i], &i);
			expanded = ft_strjoin_free(expanded, aux);
			expanded = ft_strjoin_free(expanded, var);
			start = i + 1;
		}
		i++;
	}
	aux = ft_substr(token, start, i - start);
	expanded = ft_strjoin_free(expanded, aux);
	return (expanded);
}

// quotes
char	*remove_quotes(char *str)
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

// wildcards
int	is_match(const char *str, const char *pattern)
{
	if (!*pattern)
	{
		if (!*str)
			return (1);
		else
			return (0);
	}
	if (*pattern == '*')
		return (is_match(str, pattern + 1) || (*str && is_match(str + 1, pattern)));
	else if (*pattern == *str)
		return (is_match(str + 1, pattern + 1));
	return (0);
}

void	ft_sort_str_arr(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcasecmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*arr_to_str(char **arr)
{
	char	*result;
	char	*space;
	char	*str;
	int		i;

	i = 0;
	result = NULL;
	while(arr[i])
	{
		if (!result)
			result = ft_strdup(arr[i]);
		else
		{
			space = ft_strdup(" ");
			str = ft_strdup(arr[i]);
			result = ft_strjoin_free(result, space);
			result = ft_strjoin_free(result, str);
		}
		i++;
	}
	return (result);
}

char	*expand_wildcards(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	char			*result;

	if (!pattern || !ft_strchr(pattern, '*'))
		return (ft_strdup(pattern));
	matches = allocate_mem(1, sizeof(char *));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (*(entry->d_name) != '.' && is_match(entry->d_name, pattern))
			matches = ft_arrappend(matches, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	if (ft_arrlen(matches) == 0)
	{
		ft_free_arr(matches);
		return (ft_strdup(pattern));
	}
	ft_sort_str_arr(matches);
	result = arr_to_str(matches);
	ft_free_arr(matches);
	return (result);
}

// expansor
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
		expanded = expand_wildcards(expanded); // wildcards
		expanded = remove_quotes(expanded);
		split = ft_split(expanded, ' ');
		deallocate_mem(expanded);
		j = 0;
		while (split[j])
		{
			args = ft_arrappend(args, split[j]);
			j++;
		}
		ft_free_arr(split);
		i++;
	}
	ft_free_arr(tokens);
	return (args);
}

