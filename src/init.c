/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:35:42 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/18 12:51:18 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lev	*ft_levnew(char **arr_ev)
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

t_lev	*ft_levlast(t_lev *lev)
{
	if (!lev)
		return (0);
	while (lev->next)
		lev = lev->next;
	return (lev);
}

void	ft_levadd_back(t_lev **lev, t_lev *new)
{
	t_lev	*last;

	if (!new)
		return ;
	if (!*lev)
	{
		*lev = new;
		return ;
	}
	last = ft_levlast(*lev);
	last->next = new;
	new->prev = last;
	return ;
}

t_lev	**init_lev(char **ev)
{
	int		i;
	int		len;
	char	**arr_ev;
	t_lev	*node;
	t_lev	**lev;

	i = 0;
	len = ft_arrlen(ev);
	lev = (t_lev **)malloc(len * sizeof(t_lev));
	while (!ev[i])
	{
		arr_ev = ft_split(ev[i], '=');
		node = ft_levnew(arr_ev);
		ft_arrfree(arr_ev);
		ft_levadd_back(lev, node);
		i++;
	}
	return (lev);
}

int	print_lev(t_lev **lev)
{
	t_lev	*node;

	node = *lev;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	return (0);
}

t_data	*init(char **ev)
{
	t_data	*minishell;

	minishell = malloc(sizeof(t_data));
	minishell->prompt = "minishell$ ";
	minishell->lev = init_lev(ev);
	//print_lev(minishell->lev);
	return (minishell);
}
