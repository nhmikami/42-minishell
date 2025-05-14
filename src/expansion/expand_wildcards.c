/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:29:34 by naharumi          #+#    #+#             */
/*   Updated: 2025/05/14 19:29:34 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_match(const char *str, const char *pattern)
{
	if (!*pattern)
	{
		if (!*str)
			return (1);
		else
			return (0);
	}
	if (*pattern == '*')
		return (is_match(str, pattern + 1)
			|| (*str && is_match(str + 1, pattern)));
	else if (*pattern == *str)
		return (is_match(str + 1, pattern + 1));
	return (0);
}

static void	ft_sort_str_arr(char **arr)
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

static char	*arr_to_str(char **arr)
{
	char	*result;
	char	*tab;
	char	*str;
	int		i;

	i = 0;
	result = NULL;
	while (arr[i])
	{
		if (!result)
			result = ft_strdup(arr[i]);
		else
		{
			tab = ft_strdup(" ");
			str = ft_strdup(arr[i]);
			result = ft_strjoin_free(result, tab);
			result = ft_strjoin_free(result, str);
		}
		i++;
	}
	return (result);
}

static char	**get_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;

	matches = allocate_mem(1, sizeof(char *));
	dir = opendir(".");
	if (!dir)
		return (matches);
	entry = readdir(dir);
	while (entry)
	{
		if (*(entry->d_name) != '.' && is_match(entry->d_name, pattern))
			matches = ft_arrappend(matches, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

char	*expand_wildcards(char *pattern)
{
	char	**matches;
	char	*result;

	if (!pattern || !ft_strchr(pattern, '*'))
		return (ft_strdup(pattern));
	matches = get_matches(pattern);
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
