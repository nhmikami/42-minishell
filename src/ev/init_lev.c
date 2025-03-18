/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:19:22 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 18:10:24 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lev	*levnew(char **arr_ev)
{
	t_lev	*new_node;

	new_node = (t_lev *)malloc(sizeof(t_lev));
	if (!new_node)
		handle_error(MALLOC);
	new_node->key = ft_strdup(arr_ev[0]);
	new_node->value = ft_strdup(arr_ev[1]);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_lev	*levlast(t_lev *lev)
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

t_lev	**init_lev(t_data *minishell)
{
	int		i;
	char	**arr_ev;
	t_lev	*node;
	t_lev	**lev;

	i = 0;
	minishell->ev_num = arrlen(minishell->ev);
	lev = (t_lev **)malloc(sizeof(t_lev *));
	if (!lev)
		handle_error(MALLOC);
	*lev = NULL;
	while (minishell->ev[i] != NULL)
	{
		arr_ev = ft_split(minishell->ev[i], '=');
		node = levnew(arr_ev);
		arrfree(arr_ev);
		levadd_back(lev, node);
		i++;
	}
	return (lev);
}
