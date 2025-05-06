/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:19:22 by cayamash          #+#    #+#             */
/*   Updated: 2025/04/02 18:20:53 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lev	*new_lev(char **arr_ev)
{
	t_lev	*new_node;
	char	*value;
	char	*temp;
	int		i;

	new_node = allocate_mem(1, sizeof(t_lev));
	if (!new_node)
		handle_error(MALLOC);
	new_node->key = ft_strdup(arr_ev[0]);
	new_node->value = ft_strdup("");
	i = 1;
	while (arr_ev[i])
	{
		value = ft_strdup(arr_ev[i]);
		if (i > 1)
			temp = ft_strjoin(new_node->value, "=");
		else
			temp = ft_strdup(new_node->value);
		deallocate_mem(new_node->value);
		new_node->value = ft_strjoin_free(temp, value);
		i++;
	}
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_lev	*levlast(t_lev *lev)
{
	if (!lev)
		return (0);
	while (lev->next)
		lev = lev->next;
	return (lev);
}

void	levadd_back(t_lev **lev, t_lev *new)
{
	t_lev	*last;

	if (!new)
		return ;
	if (!*lev)
	{
		*lev = new;
		return ;
	}
	last = levlast(*lev);
	last->next = new;
	new->prev = last;
	return ;
}

char **separate_ev(char *str)
{
	int	len_key;
	int	len_value;
	char *key;
	char *value;
	char **ev;

	len_key = 0;
	while(str[len_key] != '=' && str[len_key] != '\0')
		len_key++;
	key = allocate_mem(len_key + 2, sizeof(char));
	ft_strlcpy(key, str, len_key + 1);
	len_value = 0;
	while(str[len_key + 1 + len_value] != '\0')
		len_value++;
	value = allocate_mem(len_value + 2, sizeof(char));
	ft_strlcpy(value, str + len_key + 1, len_value + 1);
	ev = allocate_mem(3, sizeof(char *));
	ev[0] = key;
	ev[1] = value;
	ev[2] = NULL;
	return (ev);
}

t_lev	**init_lev(t_data *minishell)
{
	int		i;
	char	**arr_ev;
	t_lev	*node;
	t_lev	**lev;

	i = 0;
	minishell->ev_num = arrlen(minishell->ev);
	lev = allocate_mem(1, sizeof(t_lev *));
	if (!lev)
		handle_error(MALLOC);
	*lev = NULL;
	while (minishell->ev[i] != NULL)
	{
		arr_ev = separate_ev(minishell->ev[i]);
		node = new_lev(arr_ev);
		ft_free_arr(arr_ev);
		levadd_back(lev, node);
		i++;
	}
	return (lev);
}
