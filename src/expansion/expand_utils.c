/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:31:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/26 14:31:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_key_value(t_lev *lev, char *key)
{
	t_lev	*env_var;

	env_var = findlev(lev, key);
	if (!env_var || !env_var->value)
		return (NULL);
	return (env_var->value);
}
