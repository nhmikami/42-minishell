/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:18:29 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 18:09:48 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lev	*findlev(t_lev *lev, char *key)
{
	int	len;

	len = ft_strlen(key);
	if (!lev)
		return (0);
	while (lev)
	{
		if (!ft_strncmp(lev->key, key, len))
			return (lev);
		lev = lev->next;
	}
	return (NULL);
}

int	levdel(t_lev **lev, char *key)
{
	t_lev	*node;

	node = findlev(*lev, key);
	if (!node)
		return (1);
	if (node->exported == 0)
		return (2);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node->key);
	free(node->value);
	free(node);
	return (0);
}

void	free_lev(t_lev **lev)
{
	t_lev	*node;
	t_lev	*node_next;

	if (!lev || !*lev)
		return ;
	node = *lev;
	while (node)
	{
		free(node->key);
		free(node->value);
		node_next = node->next;
		free(node);
		node = node_next;
	}
	*lev = NULL;
	free(lev);
}

char	**lev_to_array(t_data *minishell)
{
	t_lev	*node;
	char	**arr;
	int		i;

	if (!minishell)
		return (NULL);
	node = *minishell->lev;
	i = 0;
	arr = malloc((minishell->ev_num + 1) * sizeof(char *));
	if (!arr)
		handle_error(MALLOC);
	while (node)
	{
		arr[i] = concatenate(node->key, "=", node->value);
		i++;
		node = node->next;
	}
	return (arr);
}
